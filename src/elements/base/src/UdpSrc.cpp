#include "UdpSrc.h"

GSTWUdpSrc::GSTWUdpSrc(string friendlyName) : GSTWElement("udpsrc", friendlyName)
{
}

GSTWUdpSrc::~GSTWUdpSrc()
{
}


void GSTWUdpSrc::SetPort(gint value)
{
    g_object_set (this->_GstElement, "port", value, NULL);
}

void GSTWUdpSrc::SetHost(string value)
{
    g_object_set (this->_GstElement, "host", value.c_str(), NULL);
}