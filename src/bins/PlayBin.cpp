#include "PlayBin.h"

GSTWPlayBin::GSTWPlayBin(string friendlyName) : GSTWElement("playbin", friendlyName)
{
    this->Uri = new GSTWObjectProperties(this->_GstElement, "uri");
};

GSTWPlayBin::~GSTWPlayBin()
{
   delete this->Uri;
}