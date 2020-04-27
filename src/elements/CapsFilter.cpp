#include "CapsFilter.h"

GSTWCapsFilter::GSTWCapsFilter(string friendlyName) : GSTWElement("capsfilter", friendlyName)
{
}

GSTWCapsFilter::~GSTWCapsFilter()
{
}

void GSTWCapsFilter::SetCapsFromString(string value)
{
    g_object_set (this->_GstElement, "caps", value.c_str(), NULL);   
}