#include "NvStreamMux.h"

GSTWNvStreamMux::GSTWNvStreamMux(string friendlyName) : GSTWElement("nvstreammux", friendlyName)
{
}

GSTWNvStreamMux::~GSTWNvStreamMux()
{
}

void GSTWNvStreamMux::SetWidth(gint value)
{
    g_object_set (this->_GstElement, "width", value, NULL);   
}
 
void GSTWNvStreamMux::SetHeight(gint value)
{
g_object_set (this->_GstElement, "height", value, NULL);
}

void GSTWNvStreamMux::SetBatchSize(gint value)
{
g_object_set (this->_GstElement, "batch-size", value, NULL);
}

void GSTWNvStreamMux::SetBatchedPushTimeout(gint value)
{
g_object_set (this->_GstElement, "batched-push-timeout", value, NULL);
}

GSTWRequestPad* GSTWNvStreamMux::GetRequestPad()
{
    return new GSTWRequestPad(this->_GstElement, "sink_0");
}