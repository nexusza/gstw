#include "gst/gst.h"
#include "Element.h"

GSTWElement::GSTWElement(string elementName, string friendlyName)
{
    this->FriendlyName = friendlyName;
    this->_GstElement = nullptr;
    this->Factory = new GSTWElementFactory(elementName);
}

GSTWElement::GSTWElement(GstElement *_gstElement)
{
    //note: the factory will actually not work as the element name given here is the friendly name not the factory name
    //How to get static pads of an unknown element at runtime?
    this->_GstElement = _gstElement;
    this->Factory = new GSTWElementFactory(gst_element_get_name(_gstElement));
}

GSTWElement::~GSTWElement()
{
    delete this->Factory;
    this->Factory = nullptr;
    this->_GstElement = nullptr;
}

string GSTWElement::GetName()
{
    return gst_element_get_name(this->_GstElement);
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
    if(element->_GstElement != nullptr)
    {
        if (gst_element_link(this->_GstElement, element->_GstElement) != TRUE)
        {
            g_print("Element '%s' could not be linked to '%s'.\n", this->FriendlyName.c_str(), element->FriendlyName.c_str());
        }
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