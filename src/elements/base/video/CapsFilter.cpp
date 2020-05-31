#include "CapsFilter.h"
#include "gst/gst.h"

GSTWCapsFilter::GSTWCapsFilter(string friendlyName) : GSTWElement("capsfilter", friendlyName)
{
}

GSTWCapsFilter::~GSTWCapsFilter()
{
}

void GSTWCapsFilter::SetCapsFromString(string value)
{
    GstCaps *caps = gst_caps_from_string(value.c_str());

    g_object_set (this->_GstElement, "caps", caps, NULL);   
}