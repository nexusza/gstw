#include "gst/gst.h"
#include "Element.h"
#include "format.h"

GSTWSignalHandler::GSTWSignalHandler()
{

}

GSTWSignalHandler::~GSTWSignalHandler()
{
    
}

GSTWElement::GSTWElement(string elementName, string friendlyName)
{
    this->FriendlyName = friendlyName;
    this->_GstElement = nullptr;
    this->Factory = new GSTWElementFactory(elementName);
}

GSTWElement::GSTWElement(GstElement *_gstElement)
{
    
    this->_GstElement = _gstElement;
    //note: the factory will actually not work as the element name given here is the friendly name not the factory name
    //How to get static pads of an unknown element at runtime?
    //this->Factory = new GSTWElementFactory(gst_element_get_name(_gstElement));
    this->Factory = nullptr;
}

GSTWElement::~GSTWElement()
{
    if(this->Factory != nullptr)
    {
        delete this->Factory;
        this->Factory = nullptr;
    }
    
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

GSTWElement* GSTWElement::AutoLinkElement(GSTWElement *element)
{
    if(element->_GstElement != nullptr)
    {
        if (gst_element_link(this->_GstElement, element->_GstElement) != TRUE)
        {
            g_print("Element '%s' could not be linked to '%s'.\n", this->FriendlyName.c_str(), element->FriendlyName.c_str());
        }
    }

    return element;
}

GSTWStaticPad *GSTWElement::GetSinkStaticPad()
{
    return new GSTWStaticPad(this->_GstElement, "sink");
}

GSTWRequestPad *GSTWElement::GetSinkRequestPad(gint index)
{
    return new GSTWRequestPad(this->_GstElement, fmt::format("sink_{0}", index));    
}

GSTWStaticPad *GSTWElement::GetSrcStaticPad()
{
    return new GSTWStaticPad(this->_GstElement, "src");
}

GSTWRequestPad *GSTWElement::GetSrcRequestPad(gint index)
{
    return new GSTWRequestPad(this->_GstElement, fmt::format("src_{0}", index));    
}

bool GSTWElement::GetStaticPadTemplates(GSTWStaticPadTemplate **staticTemplate)
{
    if(this->Factory == nullptr)
    {
        return false;
    }

    return this->Factory->GetStaticPadTemplates(staticTemplate);
}

void GSTWElement::ConnectToSignal(GSTWSignalHandler* handler)
{
    handler->ConnectToSignal(this);
}