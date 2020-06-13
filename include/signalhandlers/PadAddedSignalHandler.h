#include "Element.h"

#ifndef GSTWPADADDEDSIGNALHANDLER_H
#define GSTWPADADDEDSIGNALHANDLER_H

class GSTWPadAddedSignalHandler : public GSTWSignalHandler
{
private:
    GSTWPadFilter* padFilter;
public:
    GSTWPadAddedSignalHandler();
    ~GSTWPadAddedSignalHandler();
    void ConnectToSignal(GSTWElement* element);
    void UsePadFilter(GSTWPadFilter* padFilter);
    void HandlePadAddedSignal(GstElement *element, GstPad* pad);
protected:
    virtual void OnHandlePadAddedSignal(GSTWElement *element, GSTWDynamicPad* pad) = 0;
};

static void gstw_pad_added_signal(GstElement *src, GstPad *new_pad, GSTWPadAddedSignalHandler *handler);

#endif
