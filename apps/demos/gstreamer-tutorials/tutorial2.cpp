#include <iostream>
#include "All.h"

int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    GSTWCustomPipeline *pipeline = new GSTWCustomPipeline("mypipeline");  
    GSTWVideoTestSrc *source = new GSTWVideoTestSrc("source");
    GSTWAutoVideoSink *sink = new GSTWAutoVideoSink("sink");
    
    pipeline->CreateElement();

    pipeline->AddElement(source);
    pipeline->AddElement(sink);

    source->AutoLinkElement(sink);

    source->SetPattern(0);

    pipeline->SetToPlayingState();

    GSTWBus *bus = pipeline->GetBus();

    bus->BeginWait();

    delete bus;
    
    pipeline->SetToNullState();

    delete source;
    delete sink;
    delete pipeline;

    return 0;
}