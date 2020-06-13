#include <iostream>
#include "All.h"
#include "format.h"
#include "gstnvdsmeta.h"

/*
It is meant for simple demonstration of how to use the various DeepStream SDK
elements in the pipeline and extract meaningful insights from a video stream.

This sample creates instance of "nvinfer" element. Instance of
the "nvinfer" uses TensorRT API to execute inferencing on a model. Using a
correct configuration for a nvinfer element instance is therefore very
important as considerable behaviors of the instance are parameterized
through these configs.

For reference, here are the config files used for this sample :
1. The 4-class detector (referred to as pgie in this sample) uses
    dstest1_pgie_config.txt

In this sample, we first create one instance of "nvinfer", referred as the pgie.
This is our 4 class detector and it detects for "Vehicle , RoadSign, TwoWheeler,
Person".
nvinfer element attach some MetaData to the buffer. By attaching
the probe function at the end of the pipeline, one can extract meaningful
information from this inference. Please refer the "osd_sink_pad_buffer_probe"
function in the sample code. For details on the Metadata format, refer to the
file "gstnvdsmeta.h"
*/

#define MAX_DISPLAY_LEN 64

#define PGIE_CLASS_ID_VEHICLE 0
#define PGIE_CLASS_ID_PERSON 2

/* The muxer output resolution must be set if the input streams will be of
 * different resolution. The muxer will scale all the input frames to this
 * resolution. */
#define MUXER_OUTPUT_WIDTH 1920
#define MUXER_OUTPUT_HEIGHT 1080

/* Muxer batch formation timeout, for e.g. 40 millisec. Should ideally be set
 * based on the fastest source's framerate. */
#define MUXER_BATCH_TIMEOUT_USEC 4000000

///home/nanonexusza/Downloads/deepstream_sdk_v4.0.2_jetson/samples/streams/sample_1080p_h264.mp4

gint frame_number = 0;
gchar pgie_classes_str[4][32] = { "Vehicle", "TwoWheeler", "Person",
  "Roadsign"
};

class HandlePadProbe : public GSTWPadProbeHandler
{
    void OnHandlePadProbe(GstPad* pad, GstPadProbeInfo * info)
    {
    GstBuffer *buf = (GstBuffer *) info->data;
    guint num_rects = 0; 
    NvDsObjectMeta *obj_meta = NULL;
    guint vehicle_count = 0;
    guint person_count = 0;
    NvDsMetaList * l_frame = NULL;
    NvDsMetaList * l_obj = NULL;
    NvDsDisplayMeta *display_meta = NULL;

    NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta (buf);

    for (l_frame = batch_meta->frame_meta_list; l_frame != NULL;
      l_frame = l_frame->next) {
        NvDsFrameMeta *frame_meta = (NvDsFrameMeta *) (l_frame->data);
        int offset = 0;
        for (l_obj = frame_meta->obj_meta_list; l_obj != NULL;
                l_obj = l_obj->next) {
            obj_meta = (NvDsObjectMeta *) (l_obj->data);
            if (obj_meta->class_id == PGIE_CLASS_ID_VEHICLE) {
                vehicle_count++;
                num_rects++;
            }
            if (obj_meta->class_id == PGIE_CLASS_ID_PERSON) {
                person_count++;
                num_rects++;
            }
        }
        display_meta = nvds_acquire_display_meta_from_pool(batch_meta);
        NvOSD_TextParams *txt_params  = &display_meta->text_params[0];
        display_meta->num_labels = 1;
        //txt_params->display_text = g_malloc0 (MAX_DISPLAY_LEN);
        txt_params->display_text =new char[MAX_DISPLAY_LEN];
        offset = snprintf(txt_params->display_text, MAX_DISPLAY_LEN, "Person(s) = %d ", person_count);
        offset = snprintf(txt_params->display_text + offset , MAX_DISPLAY_LEN, "Vehicle(s) = %d ", vehicle_count);

        // Now set the offsets where the string should appear 
        txt_params->x_offset = 10;
        txt_params->y_offset = 12;
        //gchar pad_name_src[16] = "src";
        gchar serif[16] = "Serif";

        // Font , font-color and font-size 
        txt_params->font_params.font_name = serif;
        txt_params->font_params.font_size = 10;
        txt_params->font_params.font_color.red = 1.0;
        txt_params->font_params.font_color.green = 1.0;
        txt_params->font_params.font_color.blue = 1.0;
        txt_params->font_params.font_color.alpha = 1.0;

        // Text background color 
        txt_params->set_bg_clr = 1;
        txt_params->text_bg_clr.red = 0.0;
        txt_params->text_bg_clr.green = 0.0;
        txt_params->text_bg_clr.blue = 0.0;
        txt_params->text_bg_clr.alpha = 1.0;

        nvds_add_display_meta_to_frame(frame_meta, display_meta);
    }
    g_print ("Frame Number = %d Number of objects = %d "
            "Vehicle Count = %d Person Count = %d\n",
            frame_number, num_rects, vehicle_count, person_count);
    frame_number++;
    }
};

int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    GSTWCustomPipeline *pipeline = new GSTWCustomPipeline("mypipeline");
    GSTWMessageLogger *logger = new GSTWMessageLogger(pipeline);
    GSTWFileSrc *source = new GSTWFileSrc("httpsource");
    GSTWQtDemux *qtdemux = new GSTWQtDemux("demux");
    GSTWQueue *queue = new GSTWQueue("queue");
    GSTWH264Parse *parse = new GSTWH264Parse("parse");
    GSTWNvv4l2Decoder *decode = new GSTWNvv4l2Decoder("decode");
    GSTWNvStreamMux *mux = new GSTWNvStreamMux("mux");
    GSTWNvInfer *pgie = new GSTWNvInfer("infer");
    GSTWNvDsosd *osd = new GSTWNvDsosd("osd");
    GSTWNvVideoConvert *convert = new GSTWNvVideoConvert("convert");
    GSTWNvVideoConvert *convertosd = new GSTWNvVideoConvert("convertosd");
    GSTWCapsFilter *caps = new GSTWCapsFilter("caps");
    GSTWNvv4l2H264Enc *encode = new GSTWNvv4l2H264Enc("encode");
    GSTWRtph264Pay *payload = new GSTWRtph264Pay("rtppayload");
    GSTWUdpSink *udp = new GSTWUdpSink("udpsink");

    pipeline->CreateElement();

    pipeline->AddElement(source);
    pipeline->AddElement(qtdemux);
    pipeline->AddElement(queue);
    pipeline->AddElement(parse);
    pipeline->AddElement(decode);
    pipeline->AddElement(mux);
    pipeline->AddElement(pgie);
    pipeline->AddElement(convert);
    pipeline->AddElement(osd);
    pipeline->AddElement(convertosd);
    pipeline->AddElement(caps);
    pipeline->AddElement(encode);
    pipeline->AddElement(payload);
    pipeline->AddElement(udp);
   
    pgie->SetConfigFilePath("/home/nanonexusza/Development/git/gstw/apps/demos/nvidia/deepstreamsdk/config/nvidiatest1.txt");

    GSTWStaticPad* decodeSrc = decode->GetSrcStaticPad();
    GSTWRequestPad *muxRequestPad = mux->GetSinkRequestPad(0);

    decodeSrc->LinkPad(muxRequestPad);

    source->AutoLinkElement(qtdemux);

    queue
    ->AutoLinkElement(parse)
    ->AutoLinkElement(decode);

    mux
    ->AutoLinkElement(pgie)
    ->AutoLinkElement(convert)
    ->AutoLinkElement(osd)
    ->AutoLinkElement(convertosd)
    ->AutoLinkElement(caps)
    ->AutoLinkElement(encode)
    ->AutoLinkElement(payload)
    ->AutoLinkElement(udp);  

    GSTWVideoPadFilter* videoFilter = new GSTWVideoPadFilter();

    GSTWLinkToSinkPadSignalHandler* demuxHandler = new GSTWLinkToSinkPadSignalHandler(queue);

    demuxHandler->UsePadFilter(videoFilter);

    qtdemux->ConnectToSignal(demuxHandler);

    caps->SetCapsFromString("video/x-raw(memory:NVMM), width=(int)1920, height=(int)1080, format=(string)NV12, framerate=(fraction)30/1");

    mux->SetWidth(MUXER_OUTPUT_WIDTH);
    mux->SetHeight(MUXER_OUTPUT_HEIGHT);
    mux->SetBatchSize(1);
    mux->SetBatchedPushTimeout(MUXER_OUTPUT_HEIGHT);

    GSTWStaticPad* osdSinkPad = osd->GetSinkStaticPad();
    HandlePadProbe* probe = new HandlePadProbe();

    osdSinkPad->Probe(probe);
    
    source->SetLocation("/home/nanonexusza/Downloads/deepstream_sdk_v4.0.2_jetson/samples/streams/sample_1080p_h264.mp4");

    udp->SetHost("192.168.1.50");

    udp->SetPort(5000);

    pipeline->SetToPlayingState();

    GSTWBus *bus = pipeline->GetBus();

    bus->AddMessageHandler(logger);

    bus->BeginWait();

    delete logger;
    delete bus;

    pipeline->SetToNullState();

    delete pipeline;

    return 0;
}