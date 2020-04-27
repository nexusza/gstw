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

void GSTWUdpSink::SetUri(string value)
{
    g_object_set (this->_GstElement, "uri", value.c_str(), NULL);
}