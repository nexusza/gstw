#include "Element.h"

#ifndef GSTWRTPH264PAY_H
#define GSTWRTPH264PAY_H

//https://gstreamer.freedesktop.org/documentation/x264/index.html
class GSTWRtph264Pay : public GSTWElement
{
private:
    /* data */
public:
    GSTWRtph264Pay(string friendlyName);
    ~GSTWRtph264Pay();
};

#endif