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

    source->Link(sink);

    source->Pattern()->Set(0);

    pipeline->Play();

    pipeline->WaitUntilEnd();
    
    pipeline->Stop();

    delete source;
    delete sink;
    delete pipeline;

    return 0;
}