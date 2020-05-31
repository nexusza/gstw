#include "CustomBin.h"

GSTWCustomBin::GSTWCustomBin(string friendlyName) : GSTWBin(friendlyName, friendlyName)
{
}

GSTWCustomBin::~GSTWCustomBin()
{
}

void GSTWCustomBin::CreateElement()
{
    this->_GstElement = gst_bin_new(this->FriendlyName.c_str());
}