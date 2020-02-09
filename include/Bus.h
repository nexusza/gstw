#include "gst/gst.h"
#include "Message.h"

#ifndef GSTWBUS_H
#define GSTWBUS_H

class GSTWBus
{
private:
    /* data */
public:
    GSTWBus(GstBus* bus);
    ~GSTWBus();
    GstBus* _GstBus;
    GSTWMessage* GetMessage(int timeout);
};

#endif