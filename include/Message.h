#include "gst/gst.h"

#ifndef GSTWMESSAGE_H
#define GSTWMESSAGE_H

class GSTWMessage
{
private:
    bool unrefMessage;
public:
    GSTWMessage(GstMessage *message, bool unrefMessage);
    ~GSTWMessage();
    GstMessage *_GstMessage;
    GstState OldState;
    GstState NewState;
    GstState PendingState;
    gboolean IsForElement(GstElement* element);
    gboolean IsPlaying();
    gboolean IsPaused();
    gboolean IsInState(GstState state);
    void LoadStateChangedStates();
};

#endif