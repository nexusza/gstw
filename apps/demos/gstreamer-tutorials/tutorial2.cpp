#include <iostream>
#include "All.h"

int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    GSTWPipeline *pipeline = new GSTWPipeline("mypipeline");  
    GSTWVideoTestSrc *source = new GSTWVideoTestSrc("source");
    GSTWAutoVideoSink *sink = new GSTWAutoVideoSink("sink");

    pipeline->AddElement(source);
    pipeline->AddElement(sink);

    source->Link(sink);

    source->Pattern->Set(0);

    pipeline->Play();

    pipeline->WaitUntilEnd();
    
    pipeline->Stop();

    delete source;
    delete sink;
    delete pipeline;

    return 0;
}