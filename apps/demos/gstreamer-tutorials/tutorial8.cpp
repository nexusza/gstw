#include "All.h"
#include <gst/audio/audio.h>

#define CHUNK_SIZE 1024   /* Amount of bytes we are sending in each buffer */
#define SAMPLE_RATE 44100 /* Samples per second we are sending */

class CustomData;

static gboolean push_data(CustomData *data);

class CustomData : public GSTWBusMessageHandler,
                   public GSTWAppSrcChangedEventHandler,
                   public GSTWAppSinkChangedEventHandler
{
public:
    GMainLoop *main_loop;
    guint64 num_samples; /* Number of samples generated so far (for timestamp generation) */
    gfloat a, b, c, d;   /* For waveform generation */
    guint sourceid;      /* To control the GSource */
    GSTWAppSrc *app_source;
    GSTWAppSink *sink;

protected:
    void OnHandleError(GstBus *_gstBus, GSTWMessage *message)
    {
        g_main_loop_quit(this->main_loop);
    }

    void OnHandleNeedData(GstElement *source, guint size)
    {
        if (sourceid == 0)
        {
            g_print("Start feeding\n");
            sourceid = g_idle_add((GSourceFunc)push_data, this);
        }
    }

    void OnHandleEnoughData(GstElement *source)
    {
        if (sourceid != 0)
        {
            g_print("Stop feeding\n");
            g_source_remove(sourceid);
            sourceid = 0;
        }
    }

    GstFlowReturn OnHandleNewSample(GstElement *source)
    {
        GstSample *sample = sink->EmitPullSample();
        
        if (sample)
        {
            /* The only thing we do in this example is print a * to indicate a received buffer */
            g_print("*");
            gst_sample_unref(sample);
            return GST_FLOW_OK;
        }

        return GST_FLOW_ERROR;
    }
};

static gboolean push_data(CustomData *data)
{
    GSTWBuffer *buffer = new GSTWBuffer();
    gint num_samples = CHUNK_SIZE / 2; 
    GstMapInfo map;
    gint16 *raw;
    gfloat freq;

    buffer->CreateBuffer(CHUNK_SIZE);
    buffer->SetTimestamp(data->num_samples, GST_SECOND, SAMPLE_RATE);
    buffer->SetDuration(num_samples, GST_SECOND, SAMPLE_RATE);

    gst_buffer_map(buffer->_gstBuffer, &map, GST_MAP_WRITE);
    raw = (gint16 *)map.data;
    data->c += data->d;
    data->d -= data->c / 1000;
    freq = 1100 + 1000 * data->d;

    for (int i = 0; i < num_samples; i++)
    {
        data->a += data->b;
        data->b -= data->a / freq;
        raw[i] = (gint16)(500 * data->a);
    }

    gst_buffer_unmap(buffer->_gstBuffer, &map);

    data->num_samples += num_samples;

    GstFlowReturn ret = data->app_source->EmitPushBuffer(buffer);

    delete buffer;

    if (ret != GST_FLOW_OK)
    {
        return FALSE;
    }

    return TRUE;
}

int main(int argc, char *argv[])
{
    CustomData data;

    data.b = 1;
    data.d = 1;

    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    GSTWAppSrc *app_source = new GSTWAppSrc("audio_source");
    GSTWTee *tee = new GSTWTee("tee");
    GSTWQueue *audio_queue = new GSTWQueue("audio_queue");
    GSTWAudioConvert *audio_convert1 = new GSTWAudioConvert("audio_convert1");
    GSTWAudioResample *audio_resample = new GSTWAudioResample("audio_resample");
    GSTWAutoAudioSink *audio_sink = new GSTWAutoAudioSink("audio_sink");
    GSTWQueue *video_queue = new GSTWQueue("video_queue");
    GSTWAudioConvert *audio_convert2 = new GSTWAudioConvert("audio_convert2");
    GSTWWaveScope *visual = new GSTWWaveScope("visual");
    GSTWVideoConvert *video_convert = new GSTWVideoConvert("video_convert");
    GSTWAutoVideoSink *video_sink = new GSTWAutoVideoSink("video_sink");
    GSTWQueue *app_queue = new GSTWQueue("app_queue");
    GSTWAppSink *app_sink = new GSTWAppSink("app_sink");
    GSTWCustomPipeline *pipeline = new GSTWCustomPipeline("test_pipline");
    GSTWMessageLogger *logger = new GSTWMessageLogger(pipeline);
    GSTWAudioInfo audioInfo;

    data.app_source = app_source;
    data.sink = app_sink;

    pipeline->CreateElement();

    pipeline->AddElement(app_source);
    pipeline->AddElement(tee);
    pipeline->AddElement(audio_queue);
    pipeline->AddElement(audio_convert1);
    pipeline->AddElement(audio_resample);
    pipeline->AddElement(audio_sink);
    pipeline->AddElement(video_queue);
    pipeline->AddElement(audio_convert2);
    pipeline->AddElement(visual);
    pipeline->AddElement(video_convert);
    pipeline->AddElement(video_sink);
    pipeline->AddElement(app_queue);
    pipeline->AddElement(app_sink);

    visual->Shader(0);
    visual->Style(1);

    audioInfo.SetFormat(GST_AUDIO_FORMAT_S16, SAMPLE_RATE, 1, NULL);
    
    app_source->SetFormat(GST_FORMAT_TIME);
    app_source->OnNeedData(&data);
    app_source->OnEnoughData(&data);

    app_sink->SetEmitSignals(TRUE);
    app_sink->OnNewSample(&data);

    GSTWCapabilities *audio_caps = audioInfo.CreateAudioCaps();

    app_source->SetCaps(audio_caps);
    app_sink->SetCaps(audio_caps);

    delete audio_caps;

    app_source->AutoLinkElement(tee);

    audio_queue->AutoLinkElement(audio_convert1);
    audio_convert1->AutoLinkElement(audio_resample);
    audio_resample->AutoLinkElement(audio_sink);

    video_queue->AutoLinkElement(audio_convert2);
    audio_convert2->AutoLinkElement(visual);
    visual->AutoLinkElement(video_convert);
    video_convert->AutoLinkElement(video_sink);

    app_queue->AutoLinkElement(app_sink);

    GSTWRequestPad *tee_audio_pad = tee->LinkToElementSinkPad(audio_queue);
    GSTWRequestPad *tee_video_pad = tee->LinkToElementSinkPad(video_queue);
    GSTWRequestPad *tee_app_sink_pad = tee->LinkToElementSinkPad(app_queue);

    GSTWBus *bus = pipeline->GetBus();

    bus->AddMessageHandler(logger);

    bus->BeginWatch();

    //string file = "result.dot";
    //GST_DEBUG_BIN_TO_DOT_FILE((GstBin*)pipeline->_GstElement, GST_DEBUG_GRAPH_SHOW_ALL, file.c_str());

    pipeline->SetToPlayingState();

    data.main_loop = g_main_loop_new(NULL, FALSE);

    g_main_loop_run(data.main_loop);



    pipeline->SetToNullState();

    delete tee_audio_pad;
    delete tee_video_pad;
    delete tee_app_sink_pad;
    delete app_source;
    delete app_sink;
    delete tee;
    delete audio_queue;
    delete audio_convert1;
    delete audio_convert2;
    delete audio_resample;
    delete audio_sink;
    delete video_queue;
    delete visual;
    delete video_convert;
    delete video_sink;
    delete bus;
    delete pipeline;

    return 0;
}