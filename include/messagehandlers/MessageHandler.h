#include "gst/gst.h"
#include "Message.h"
#include "Element.h"

#ifndef GSTWMESSAGEHANDLER_H
#define GSTWMESSAGEHANDLER_H

class GSTWMessageHandler
{
private:
    /* data */
protected:
    virtual void OnHandleStateChanged(GSTWMessage *message);
    virtual void OnHandleError(GSTWMessage *message);
    virtual void OnHandleEOS(GSTWMessage *message);
    virtual void OnHandleOther(GSTWMessage *message);
    virtual void OnHandleDurationChange(GSTWMessage *message);
    virtual void OnHandleTimeout();

public:
    GSTWMessageHandler();
    ~GSTWMessageHandler();
    
    void HandleStateChanged(GSTWMessage *message);
    void HandleError(GSTWMessage *message);
    void HandleEOS(GSTWMessage *message);
    void HandleOther(GSTWMessage *message);
    void HandleDurationChange(GSTWMessage *message);
    void HandleTimeout();
};

#endif