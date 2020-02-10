#include <iostream>
#include "All.h"

int main (int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init (&argc, &argv);

    GSTWPipeline* pipeline = new GSTWPipeline("mypipeline");

    GSTWPlayBin* source = new GSTWPlayBin("source");
    
    GSTWMessageLogger* messageLogger = new GSTWMessageLogger(source);

    GSTWSeeker* seeker = new GSTWSeeker(source);

    pipeline->AddMessageHandler(messageLogger);
    
    pipeline->AddMessageHandler(seeker);
    
    source->Uri->Set("https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm");

    pipeline->AddElement(source);

    pipeline->Play();

    pipeline->WaitUntilEnd(100);

    pipeline->Stop();

    delete messageLogger;
    delete seeker;
    delete source;
    delete pipeline;

    return 0;
}