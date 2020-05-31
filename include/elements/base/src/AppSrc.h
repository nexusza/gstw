#include "Buffer.h"
#include "Element.h"

#ifndef GSTWAPPSRC_H
#define GSTWAPPSRC_H

class GSTWAppSrcChangedEventHandler
{
private:
    /* data */
public:
    void HandleNeedData(GstElement *source, guint size);
    void HandleEnoughData(GstElement *source);

protected:
    virtual void OnHandleNeedData(GstElement *source, guint size);
    virtual void OnHandleEnoughData(GstElement *source);
};

//https://gstreamer.freedesktop.org/documentation/app/appsrc.html
class GSTWAppSrc : public GSTWElement
{
private:
    /* data */
public:
    GSTWAppSrc(string friendlyName);
    ~GSTWAppSrc();

    void SetCaps(GSTWCapabilities *caps);
    void SetFormat(GstFormat format);

    GstFlowReturn EmitPushBuffer(GSTWBuffer *buffer);
    void OnNeedData(GSTWAppSrcChangedEventHandler *handler);
    void OnEnoughData(GSTWAppSrcChangedEventHandler *handler);
};

static void appsrc_need_data(GstElement *source, guint size, GSTWAppSrcChangedEventHandler *handler);
static void appsrc_enough_data(GstElement *source, GSTWAppSrcChangedEventHandler *handler);

#endif