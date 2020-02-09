#include "gst/gst.h"
#include "Pad.h"

#ifndef GSTWSINKPAD_H
#define GSTWSINKPAD_H

class GSTWSinkPad : public GSTWPad
{
private:
    /* data */
public:
    GSTWSinkPad(GstElement* _gstElement);
    ~GSTWSinkPad();
};

#endif