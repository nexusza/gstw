#include "gst/gst.h"
#include "Element.h"
#include "PadAddedSignalHandler.h"

#ifndef GSTWLINKTOSINKPADSIGNALHANDLER_H
#define GSTWLINKTOSINKPADSIGNALHANDLER_H

class GSTWLinkToSinkPadSignalHandler : public GSTWPadAddedSignalHandler
{
protected:
    GSTWElement* element;
    void OnHandlePadAddedSignal(GSTWElement *element, GSTWDynamicPad* pad);
public:
    GSTWLinkToSinkPadSignalHandler(GSTWElement* element);
    ~GSTWLinkToSinkPadSignalHandler();
};

#endif