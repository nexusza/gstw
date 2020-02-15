#include "Bin.h"

GSTWBin::GSTWBin(string elementName, string friendlyName) : GSTWElement(elementName, friendlyName)
{
}

GSTWBin::~GSTWBin()
{
}

void GSTWBin::AddElement(GSTWElement *element)
{
    element->CreateElement();
    gst_bin_add(GST_BIN(this->_GstElement), element->_GstElement);
}