#include "gst/gst.h"

#ifndef GSTWBUFFER_H
#define GSTWBUFFER_H

class GSTWBuffer
{
private:
    /* data */
public:
    GSTWBuffer();
    ~GSTWBuffer();
    GstBuffer *_gstBuffer;
    void CreateBuffer(gsize size);
    void SetTimestamp(guint64 val, guint64 num, guint64 denom);
    void SetDuration(guint64 val, guint64 num, guint64 denom);
};

#endif