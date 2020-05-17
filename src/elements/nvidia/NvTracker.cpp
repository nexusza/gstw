#include "NvTracker.h"

GSTWNvTracker::GSTWNvTracker(string friendlyName) : GSTWElement("nvtracker", friendlyName)
{
}

GSTWNvTracker::~GSTWNvTracker()
{
}

void GSTWNvTracker::SetWidth(gint value)
{
    g_object_set (this->_GstElement, "tracker-width", value, NULL);   
}

void GSTWNvTracker::SetHeight(gint value)
{
    g_object_set (this->_GstElement, "tracker-height", value, NULL);   
}

void GSTWNvTracker::SetGpuId(guint value)
{
    g_object_set (this->_GstElement, "gpu_id", value, NULL);   
}

void GSTWNvTracker::SetLLConfigFile(string value)
{
    g_object_set (this->_GstElement, "ll-config-file", value.c_str(), NULL);   
}

void GSTWNvTracker::SetLLLibFile(string value)
{
    g_object_set (this->_GstElement, "ll-lib-file", value.c_str(), NULL);   
}

void GSTWNvTracker::SetEnableBatchProcessing(gboolean value)
{
    g_object_set (this->_GstElement, "enable_batch_process", value, NULL);   
}
