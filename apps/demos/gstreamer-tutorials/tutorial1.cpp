#include <iostream>
#include "All.h"

int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    GSTWPlayBin *playbin = new GSTWPlayBin("mybin");

    playbin->CreateElement();

    playbin->Uri()->Set("https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm");

    playbin->Play();

    GSTWBus *bus = playbin->GetBus();

    bus->BeginWait();

    delete bus;

    playbin->Stop();

    delete playbin;

    return 0;
}