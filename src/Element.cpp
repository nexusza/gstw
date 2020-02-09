#include "gst/gst.h"
#include "Element.h"

GSTWElement::GSTWElement(string elementName, string friendlyName)
{
    this->ElementName = elementName;
    this->FriendlyName = friendlyName;
    this->_GstElement = gst_element_factory_make (elementName.c_str(), friendlyName.c_str());
}

GSTWElement::~GSTWElement()
{
    //gst_object_unref (this->_GstElement);
    this->_GstElement = nullptr;
}


void GSTWElement::Link(GSTWElement *element)
{
    gst_element_link (this->_GstElement, element->_GstElement);
}

GSTWSinkPad* GSTWElement::GetSinkPad()
{
    return new GSTWSinkPad(this->_GstElement);
}