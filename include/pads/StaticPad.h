#include "gst/gst.h"
#include "Pad.h"
#include "PadProbeHandler.h"

#ifndef GSTWSINKPAD_H
#define GSTWSINKPAD_H

class GSTWStaticPad : public GSTWPad
{
private:
    /* data */
public:
    GSTWStaticPad(GstElement* _gstElement, string padName);
    ~GSTWStaticPad();

    void Probe(GSTWPadProbeHandler* handler);
};

static GstPadProbeReturn gstw_pad_probe_handler_event(GstPad *pad, GstPadProbeInfo * info, gpointer data);

#endif