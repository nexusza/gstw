#include "Element.h"

#ifndef GSTWX264ENC_H
#define GSTWX264ENC_H

//https://gstreamer.freedesktop.org/documentation/x264/index.html
class GSTWX264Enc : public GSTWElement
{
private:
    /* data */
public:
    GSTWX264Enc(string friendlyName);
    ~GSTWX264Enc();
};

#endif