#include "UdpSink.h"

GSTWUdpSink::GSTWUdpSink(string friendlyName) : GSTWElement("udpsink", friendlyName)
{
}

GSTWUdpSink::~GSTWUdpSink()
{
}


void GSTWUdpSink::SetPort(gint value)
{
    g_object_set (this->_GstElement, "port", value, NULL);
}

void GSTWUdpSink::SetHost(string value)
{
    g_object_set (this->_GstElement, "host", value.c_str(), NULL);
}