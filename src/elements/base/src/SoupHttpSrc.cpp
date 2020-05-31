#include "SoupHttpSrc.h"

GSTWSoupHttpSrc::GSTWSoupHttpSrc(string friendlyName) : GSTWElement("souphttpsrc", friendlyName)
{
}

GSTWSoupHttpSrc::~GSTWSoupHttpSrc()
{
}

void GSTWSoupHttpSrc::SetLocation(string value)
{
    g_object_set (this->_GstElement, "location", value.c_str(), NULL);
}