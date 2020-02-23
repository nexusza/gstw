#include "gst/gst.h"
#include "Element.h"

GSTWElement::GSTWElement(string elementName, string friendlyName)
{
    this->FriendlyName = friendlyName;
    this->_GstElement = nullptr;
    this->Factory = new GSTWElementFactory(elementName);
}

GSTWElement::~GSTWElement()
{
    delete this->Factory;
    this->Factory = nullptr;
    this->_GstElement = nullptr;
}

void GSTWElement::CreateElement()
{
    if (this->_GstElement == nullptr)
    {
        this->_GstElement = this->Factory->CreateElement(this->FriendlyName);
    }
}

void GSTWElement::SendApplicationMessage(string messageName)
{
    gst_element_post_message(this->_GstElement,
                             gst_message_new_application(GST_OBJECT(this->_GstElement),
                                                         gst_structure_new_empty(messageName.c_str())));
}

void GSTWElement::AutoLinkElement(GSTWElement *element)
{
    if (gst_element_link(this->_GstElement, element->_GstElement) != TRUE)
    {
        g_printerr("Elements could not be linked.\n");
    }
}

GSTWStaticPad *GSTWElement::GetSinkPad()
{
    return new GSTWStaticPad(this->_GstElement, "sink");
}

bool GSTWElement::GetStaticPadTemplates(GSTWStaticPadTemplate **staticTemplate)
{
    return this->Factory->GetStaticPadTemplates(staticTemplate);
}