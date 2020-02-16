#include "UriDecodeBin.h"

GSTWUriDecodeBin::GSTWUriDecodeBin(string friendlyName) : GSTWBin("uridecodebin", friendlyName)
{
}

void GSTWUriDecodeBin::SetUri(string uri)
{
    g_object_set(this->_GstElement, "uri", uri.c_str(), NULL);
}

GSTWUriDecodeBin::~GSTWUriDecodeBin()
{
}