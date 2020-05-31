#include "gst/gst.h"
#include "Pad.h"

#ifndef GSTWDYNAMICPAD_H
#define GSTWDYNAMICPAD_H

class GSTWDynamicPad : public GSTWPad
{
public:
    GSTWDynamicPad(GstPad* _gstPad);
    ~GSTWDynamicPad();
};

#endif