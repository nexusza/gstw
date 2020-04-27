#include <iostream>
#include "All.h"

int main (int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init (&argc, &argv);

    GSTWCustomPipeline* pipeline = new GSTWCustomPipeline("mypipeline");
    GSTWUriDecodeBin* source = new GSTWUriDecodeBin("source");
    GSTWAudioConvert* convert = new GSTWAudioConvert("convert");
    GSTWAudioResample* resample = new GSTWAudioResample("resample");
    GSTWAutoAudioSink* sink = new GSTWAutoAudioSink("sink");
    GSTWPadLinkEventHandler* padAdded = new GSTWPadLinkEventHandler(convert);

    pipeline->CreateElement();

    pipeline->AddElement(source);
    pipeline->AddElement(convert);
    pipeline->AddElement(resample);
    pipeline->AddElement(sink);

    convert->AutoLinkElement(resample);
    resample->AutoLinkElement(sink);
    
    source->SetUri("https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm");

    padAdded->ConnectToPadAddedSignalAudio(source);

    pipeline->SetToPlayingState();

    GSTWBus *bus = pipeline->GetBus();

    bus->BeginWait();

    delete bus;

    pipeline->SetToNullState();

    delete source;
    delete convert;
    delete resample;
    delete sink;
    delete padAdded;
    delete pipeline;

    return 0;
}