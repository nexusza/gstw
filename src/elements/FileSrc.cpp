#include "FileSrc.h"

GSTWFileSrc::GSTWFileSrc(string friendlyName) : GSTWElement("filesrc", friendlyName)
{
}

GSTWFileSrc::~GSTWFileSrc()
{
}

void GSTWFileSrc::SetLocation(string value)
{
    g_object_set (this->_GstElement, "location", value.c_str(), NULL);
}