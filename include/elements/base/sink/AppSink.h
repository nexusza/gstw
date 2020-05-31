#include "gst/gst.h"
#include "Element.h"

#ifndef GSTWAPPSINK_H
#define GSTWAPPSINK_H

class GSTWAppSinkChangedEventHandler
{
private:
    /* data */
public:
    GstFlowReturn HandleNewSample(GstElement *sourc);

protected:
    virtual GstFlowReturn OnHandleNewSample(GstElement *source);
};

//https://gstreamer.freedesktop.org/documentation/app/appsink.html?gi-language=c
class GSTWAppSink : public GSTWElement
{
private:
    /* data */
public:
    GSTWAppSink(string friendlyName);
    ~GSTWAppSink();
    void SetCaps(GSTWCapabilities *caps);
    void SetEmitSignals(gboolean value);
    GstSample* EmitPullSample();

    void OnNewSample(GSTWAppSinkChangedEventHandler *handler);
};

static GstFlowReturn appsink_new_sample(GstElement *source, GSTWAppSinkChangedEventHandler *handler);

#endif