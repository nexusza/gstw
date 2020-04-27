#include "gst/gst.h"
#include "Element.h"
#include "Pad.h"
#include "PadLinkEventHandler.h"

GSTWPadLinkEventHandler::GSTWPadLinkEventHandler(GSTWElement *target)
{
    this->Target = target;
}

GSTWPadLinkEventHandler::~GSTWPadLinkEventHandler()
{
    this->Target = nullptr;
}

void GSTWPadLinkEventHandler::ConnectToPadAddedSignalAudio(GSTWElement *source)
{
    g_signal_connect(source->_GstElement, "pad-added", G_CALLBACK(gstw_pad_added_event_audio), this);
}

void GSTWPadLinkEventHandler::ConnectToPadAddedSignalVideo(GSTWElement *source)
{
    g_signal_connect(source->_GstElement, "pad-added", G_CALLBACK(gstw_pad_added_event_video), this);
}

static void gstw_pad_added_event_audio(GstElement *src, GstPad *new_pad, GSTWPadLinkEventHandler *data)
{
    GSTWStaticPad *sinkPad = data->Target->GetSinkPad();

    sinkPad->LinkSourcePad(src, new_pad, "audio/x-raw");

    delete sinkPad;
}

static void gstw_pad_added_event_video(GstElement *src, GstPad *new_pad, GSTWPadLinkEventHandler *data)
{
    GSTWStaticPad *sinkPad = data->Target->GetSinkPad();

    sinkPad->LinkSourcePad(src, new_pad, "video/x-raw");

    delete sinkPad;
}