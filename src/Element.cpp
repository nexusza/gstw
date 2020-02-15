#include "gst/gst.h"
#include "Element.h"

GSTWElement::GSTWElement(string elementName, string friendlyName)
{
    this->ElementName = elementName;
    this->FriendlyName = friendlyName;
    this->_GstElement = nullptr;
}

GSTWElement::~GSTWElement()
{
    this->_GstElement = nullptr;
}

void GSTWElement::CreateElement()
{
    if (this->_GstElement == nullptr)
    {
        this->_GstElement = gst_element_factory_make(this->ElementName.c_str(), this->FriendlyName.c_str());
    }
}

void GSTWElement::Link(GSTWElement *element)
{
    gst_element_link(this->_GstElement, element->_GstElement);
}

GSTWSinkPad *GSTWElement::GetSinkPad()
{
    return new GSTWSinkPad(this->_GstElement);
}