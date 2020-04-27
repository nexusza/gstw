#include "gst/gst.h"
#include "Element.h"

#ifndef GSTWUDPSRC_H
#define GSTWUDPSRC_H

//https://gstreamer.freedesktop.org/documentation/udp/udpsink.html?gi-language=c
class GSTWUdpSrc : public GSTWElement
{
private:
    /* data */
public:
    GSTWUdpSrc(string friendlyName);
    ~GSTWUdpSrc();
    void SetPort(gint value);
    void SetHost(string value);
};

#endif