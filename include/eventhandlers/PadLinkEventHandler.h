#include "gst/gst.h"

#ifndef GSTWPADLINKEVENTHANDLER_H
#define GSTWPADLINKEVENTHANDLER_H

class GSTWPadLinkEventHandler
{
private:
    /* data */
public:
    GSTWPadLinkEventHandler(GSTWElement *target, string padName);
    ~GSTWPadLinkEventHandler();

    void ConnectToPadAddedSignalAudio(GSTWElement *source);
    void ConnectToPadAddedSignalVideo(GSTWElement *source);
    void ConnectToPadAddedSignal(GSTWElement *source);

    string PadName;

    GSTWElement *Target;
};

static void gstw_pad_added_event_audio(GstElement *src, GstPad *pad, GSTWPadLinkEventHandler *data);
static void gstw_pad_added_event_video(GstElement *src, GstPad *pad, GSTWPadLinkEventHandler *data);
static void gstw_pad_added_event(GstElement *src, GstPad *pad, GSTWPadLinkEventHandler *data);

#endif