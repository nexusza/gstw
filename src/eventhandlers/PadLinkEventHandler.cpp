#include "gst/gst.h"
#include "Element.h"
#include "Pad.h"
#include "PadLinkEventHandler.h"

GSTWPadLinkEventHandler::GSTWPadLinkEventHandler(GSTWElement *target, string padName)
{
    this->Target = target;
    this->PadName = padName;
}

GSTWPadLinkEventHandler::~GSTWPadLinkEventHandler()
{
    this->Target = nullptr;
}

void GSTWPadLinkEventHandler::ConnectToPadAddedSignal(GSTWElement *source)
{
    g_signal_connect(source->_GstElement, "pad-added", G_CALLBACK(gstw_pad_added_event), this);
}

static void gstw_pad_added_event(GstElement *src, GstPad *new_pad, GSTWPadLinkEventHandler *data)
{
    GSTWStaticPad *sinkPad = data->Target->GetSinkPad();

    sinkPad->LinkSourcePad(src, new_pad, data->Target->FriendlyName, data->PadName);

    delete sinkPad;
}