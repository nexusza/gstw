#include <iostream>
#include "All.h"

int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    GSTWPipeline *pipeline = new GSTWPipeline("mypipeline");
    GSTWPlayBin *playbin = new GSTWPlayBin("mybin");

    playbin->Uri->Set("https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm");

    pipeline->AddElement(playbin);

    pipeline->Play();

    pipeline->WaitUntilEnd();

    pipeline->Stop();

    delete playbin;

    delete pipeline;

    return 0;
}