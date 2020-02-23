#include "gst/gst.h"
#include "Pad.h"

#ifndef GSTWSINKPAD_H
#define GSTWSINKPAD_H

class GSTWStaticPad : public GSTWPad
{
private:
    /* data */
public:
    GSTWStaticPad(GstElement* _gstElement, string padName);
    ~GSTWStaticPad();
};

#endif