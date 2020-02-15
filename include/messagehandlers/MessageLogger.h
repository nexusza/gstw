#include "Element.h"
#include "Message.h"
#include "Bus.h"

#ifndef GSTWMESSAGELOGGER_H
#define GSTWMESSAGELOGGER_H

class GSTWMessageLogger : public GSTWBusMessageHandler
{
private:
    /* data */
protected:
    void OnHandleStateChanged(GstBus *_gstBus, GSTWMessage *message);
    void OnHandleTimeout(GstBus *_gstBus, GSTWMessage *message);
    void OnHandleEOS(GstBus *_gstBus, GSTWMessage *message);
    void OnHandleError(GstBus *_gstBus, GSTWMessage *message);
public:
    GSTWMessageLogger();
    GSTWMessageLogger(GSTWElement *element);
    ~GSTWMessageLogger();

    GSTWElement* Element;
};

#endif