#include "UriDecodeBin.h"

GSTWUriDecodeBin::GSTWUriDecodeBin(string friendlyName) : GSTWElement("uridecodebin", friendlyName)
{
    this->Uri = new GSTWObjectProperties(this->_GstElement, "uri");
}

GSTWUriDecodeBin::~GSTWUriDecodeBin()
{
    delete this->Uri;
}