#include "UriDecodeBin.h"

GSTWUriDecodeBin::GSTWUriDecodeBin(string friendlyName) : GSTWBin("uridecodebin", friendlyName)
{
    this->uri = nullptr;
}

GSTWObjectProperties* GSTWUriDecodeBin::Uri()
{
    if(this->uri == nullptr)
    {
        this->uri = new GSTWObjectProperties(this->_GstElement, "uri");
    }

    return this->uri;
}

GSTWUriDecodeBin::~GSTWUriDecodeBin()
{
    if(this->uri != nullptr)
    {
        delete this->uri;
        this->uri = nullptr;
    }
}