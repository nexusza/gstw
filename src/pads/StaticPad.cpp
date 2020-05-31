#include "StaticPad.h"

GSTWStaticPad::GSTWStaticPad(GstElement* _gstElement, string padName) : GSTWPad()
{
    this->_GstPad = gst_element_get_static_pad(_gstElement, padName.c_str());
}

GSTWStaticPad::~GSTWStaticPad()
{
    gst_object_unref(this->_GstPad);
    this->_GstPad = nullptr;
}

void GSTWStaticPad::Probe(GSTWPadProbeHandler* handler)
{
    gst_pad_add_probe (this->_GstPad, GST_PAD_PROBE_TYPE_BUFFER, gstw_pad_probe_handler_event, handler, NULL);
}

static GstPadProbeReturn gstw_pad_probe_handler_event(GstPad *pad, GstPadProbeInfo * info, gpointer data)
{
    ((GSTWPadProbeHandler*)data)->HandlePadProbe(pad, info);

    return GST_PAD_PROBE_OK;
}