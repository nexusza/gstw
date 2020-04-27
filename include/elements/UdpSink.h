#include "gst/gst.h"
#include "Element.h"

#ifndef GSTWUDPSINK_H
#define GSTWUDPSINK_H

//https://gstreamer.freedesktop.org/documentation/udp/udpsrc.html?gi-language=c
class GSTWUdpSink : public GSTWElement
{
private:
    /* data */
public:
    GSTWUdpSink(string friendlyName);
    ~GSTWUdpSink();
    void SetPort(gint value);
    void SetUri(string value);
};

#endif