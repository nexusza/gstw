#include "Element.h"
#include "Message.h"
#include "MessageHandler.h"

#ifndef GSTWMESSAGELOGGER_H
#define GSTWMESSAGELOGGER_H

class GSTWMessageLogger : public GSTWMessageHandler
{
private:
    /* data */
protected:
    void OnHandleStateChanged(GSTWMessage *message);
    void OnHandleTimeout(GSTWMessage *message);
    void OnHandleEOS(GSTWMessage *message);
    void OnHandleError(GSTWMessage *message);
public:
    GSTWMessageLogger();
    GSTWMessageLogger(GSTWElement *element);
    ~GSTWMessageLogger();

    GSTWElement* Element;
};

#endif