#include "AppSink.h"

GstFlowReturn GSTWAppSinkChangedEventHandler::HandleNewSample(GstElement *source)
{
    return this->OnHandleNewSample(source);
}

GstFlowReturn GSTWAppSinkChangedEventHandler::OnHandleNewSample(GstElement *source)
{
    return GstFlowReturn::GST_FLOW_OK;
}

GSTWAppSink::GSTWAppSink(string friendlyName) : GSTWElement("appsink", friendlyName)
{
}

GSTWAppSink::~GSTWAppSink()
{
}

void GSTWAppSink::SetCaps(GSTWCapabilities *caps)
{
    g_object_set(this->_GstElement, "caps", caps->_GstCaps, NULL);
}

void GSTWAppSink::SetEmitSignals(gboolean value)
{
    g_object_set(this->_GstElement, "emit-signals", value, NULL);
}

GstSample *GSTWAppSink::EmitPullSample()
{
    GstSample *sample;

    g_signal_emit_by_name(this->_GstElement, "pull-sample", &sample);

    return sample;
}

void GSTWAppSink::OnNewSample(GSTWAppSinkChangedEventHandler *handler)
{
    g_signal_connect(this->_GstElement, "new-sample", G_CALLBACK(appsink_new_sample), handler);
}

GstFlowReturn appsink_new_sample(GstElement *source, GSTWAppSinkChangedEventHandler *handler)
{
    handler->HandleNewSample(source);
}