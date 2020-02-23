#include "gst/gst.h"
#include "Pad.h"

#ifndef GSTWREQUESTPAD_H
#define GSTWREQUESTPAD_H

class GSTWRequestPad : public GSTWPad
{
private:
    GstElement* _gstElement;
public:
    GSTWRequestPad(GstElement* _gstElement, string padName);
    ~GSTWRequestPad();
};

#endif