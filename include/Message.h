#include "gst/gst.h"
#include "Element.h"
#include <string>

using namespace std;

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
    gboolean IsForElement(GSTWElement* element);
    gboolean IsPlaying();
    gboolean IsPaused();
    gboolean IsInState(GstState state);
    void LoadStateChangedStates();
    string GetMessageName();

    gint ParseBufferingPercentage();
};

#endif