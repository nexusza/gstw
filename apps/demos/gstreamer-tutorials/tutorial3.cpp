#include <iostream>
#include "All.h"

int main (int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init (&argc, &argv);

    GSTWPipeline* pipeline = new GSTWPipeline("mypipeline");

    GSTWUriDecodeBin* source = new GSTWUriDecodeBin("source");
    GSTWAudioConvert* convert = new GSTWAudioConvert("convert");
    GSTWAudioResample* resample = new GSTWAudioResample("resample");
    GSTWAutoAudioSink* sink = new GSTWAutoAudioSink("sink");
    GSTWPadLinkEventHandler* padAdded = new GSTWPadLinkEventHandler(convert);

    pipeline->AddElement(source);
    pipeline->AddElement(convert);
    pipeline->AddElement(resample);
    pipeline->AddElement(sink);

    convert->Link(resample);
    resample->Link(sink);
    
    source->Uri->Set("https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm");

    padAdded->ConnectToPadAddedSignal(source);

    pipeline->Play();

    pipeline->WaitUntilEnd();

    pipeline->Stop();

    delete source;
    delete convert;
    delete resample;
    delete sink;
    delete padAdded;
    delete pipeline;

    return 0;
}