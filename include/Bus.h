#include "gst/gst.h"
#include "Message.h"
#include <vector>

using namespace std;

#ifndef GSTWBUS_H
#define GSTWBUS_H

class GSTWBusMessageHandler
{
protected:
    virtual void OnHandleStateChanged(GstBus *_gstBus, GSTWMessage *message);
    virtual void OnHandleError(GstBus *_gstBus, GSTWMessage *message);
    virtual void OnHandleEOS(GstBus *_gstBus, GSTWMessage *message);
    virtual void OnHandleOther(GstBus *_gstBus, GSTWMessage *message);
    virtual void OnHandleDurationChange(GstBus *_gstBus, GSTWMessage *message);
    virtual void OnHandleApplication(GstBus *_gstBus, GSTWMessage *message);
    virtual void OnHandleBuffering(GstBus *_gstBus, GSTWMessage *message);
    virtual void OnHandleClockLost(GstBus *_gstBus, GSTWMessage *message);
    virtual void OnHandleTimeout();

public:
    GSTWBusMessageHandler();
    ~GSTWBusMessageHandler();
    
    void HandleStateChanged(GstBus *_gstBus, GSTWMessage *message);
    void HandleError(GstBus *_gstBus, GSTWMessage *message);
    void HandleEOS(GstBus *_gstBus, GSTWMessage *message);
    void HandleOther(GstBus *_gstBus, GSTWMessage *message);
    void HandleDurationChange(GstBus *_gstBus, GSTWMessage *message);
    void HandleApplication(GstBus *_gstBus, GSTWMessage *message);
    void HandleBuffering(GstBus *_gstBus, GSTWMessage *message);
    void HandleClockLost(GstBus *_gstBus, GSTWMessage *message);
    void HandleTimeout();
};

class GSTWBus
{
private:
    /* data */
public:
    GSTWBus(GstBus *bus);
    ~GSTWBus();

    GstBus *_GstBus;

    vector<GSTWBusMessageHandler*> Handlers;

    void AddMessageHandler(GSTWBusMessageHandler* handler);

    GSTWMessage *GetMessage(int timeout);

    void BeginWatch();
    void BeginWait(guint64 timeout);
    void BeginWait();

    void HandleStateChanged(GSTWMessage *message);
    void HandleError(GSTWMessage *message);
    void HandleEOS(GSTWMessage *message);
    void HandleOther(GSTWMessage *message);
    void HandleDurationChange(GSTWMessage *message);
    void HandleApplication(GSTWMessage *message);
    void HandleBuffering(GSTWMessage *message);
    void HandleClockLost(GSTWMessage *message);
    void HandleTimeout();
};

static void bus_error(GstBus *_gstBus, GstMessage *_gstMessage, GSTWBus *bus);
static void bus_eos(GstBus *_gstBus, GstMessage *_gstMessage, GSTWBus *bus);
static void bus_state_changed(GstBus *_gstBus, GstMessage *_gstMessage, GSTWBus *bus);
static void bus_application(GstBus *_gstBus, GstMessage *_gstMessage, GSTWBus *bus);
static void bus_buffering(GstBus *_gstBus, GstMessage *_gstMessage, GSTWBus *bus);
static void bus_clocklost(GstBus *_gstBus, GstMessage *_gstMessage, GSTWBus *bus);

#endif