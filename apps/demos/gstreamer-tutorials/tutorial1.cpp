#include <iostream>
#include "All.h"

int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    GSTWPlayBin *playbin = new GSTWPlayBin("mybin");

    playbin->CreateElement();

    playbin->SetUri("https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm");

    playbin->SetToPlayingState();

    GSTWBus *bus = playbin->GetBus();

    bus->BeginWait();

    delete bus;

    playbin->SetToNullState();

    delete playbin;

    return 0;
}