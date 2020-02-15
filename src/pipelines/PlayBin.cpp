#include "PlayBin.h"

GSTWPlayBin::GSTWPlayBin(string friendlyName) : GSTWPipeline("playbin", friendlyName)
{
}

GSTWObjectProperties *GSTWPlayBin::Uri()
{
    if (this->uri == nullptr)
    {
        this->uri = new GSTWObjectProperties(this->_GstElement, "uri");
    }

    return this->uri;
}

GSTWPlayBin::~GSTWPlayBin()
{
    if (this->uri != nullptr)
    {
        delete this->uri;
        this->uri = nullptr;
    }
}