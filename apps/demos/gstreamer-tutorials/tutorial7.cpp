#include "All.h"

int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    GSTWAudioTestSrc *audio_source = new GSTWAudioTestSrc("audio_source");
    GSTWTee *tee = new GSTWTee("tee");
    GSTWQueue *audio_queue = new GSTWQueue("audio_queue");
    GSTWAudioConvert *audio_convert = new GSTWAudioConvert("audio_convert");
    GSTWAudioResample *audio_resample = new GSTWAudioResample("audio_resample");
    GSTWAutoAudioSink *audio_sink = new GSTWAutoAudioSink("audio_sink");
    GSTWQueue *video_queue = new GSTWQueue("video_queue");
    GSTWWaveScope *visual = new GSTWWaveScope("visual");
    GSTWVideoConvert *video_convert = new GSTWVideoConvert("video_convert");
    GSTWAutoVideoSink *video_sink = new GSTWAutoVideoSink("video_sink");
    GSTWCustomPipeline *pipeline = new GSTWCustomPipeline("test_pipline");

    pipeline->CreateElement();

    pipeline->AddElement(audio_source);
    pipeline->AddElement(tee);
    pipeline->AddElement(audio_queue);
    pipeline->AddElement(audio_convert);
    pipeline->AddElement(audio_resample);
    pipeline->AddElement(audio_sink);
    pipeline->AddElement(video_queue);
    pipeline->AddElement(visual);
    pipeline->AddElement(video_convert);
    pipeline->AddElement(video_sink);

    audio_source->Freq(215.0f);

    visual->Shader(0);
    visual->Style(1);

    audio_source->AutoLinkElement(tee);

    audio_queue->AutoLinkElement(audio_convert);
    audio_convert->AutoLinkElement(audio_resample);
    audio_resample->AutoLinkElement(audio_sink);

    video_queue->AutoLinkElement(visual);
    visual->AutoLinkElement(video_convert);
    video_convert->AutoLinkElement(video_sink);

    GSTWRequestPad *tee_audio_pad = tee->LinkToElementSinkPad(audio_queue);
    GSTWRequestPad *tee_video_pad = tee->LinkToElementSinkPad(video_queue);

    pipeline->SetToPlayingState();

    GSTWBus *bus = pipeline->GetBus();

    bus->BeginWait();

    pipeline->SetToNullState();

    delete tee_audio_pad;
    delete tee_video_pad;
    delete audio_source;
    delete tee;
    delete audio_queue;
    delete audio_convert;
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