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

GSTWStaticPad *GSTWElement::GetSinkPad()
{
    return new GSTWStaticPad(this->_GstElement, "sink");
}

GSTWStaticPad *GSTWElement::GetSrcPad()
{
    return new GSTWStaticPad(this->_GstElement, "src");
}

bool GSTWElement::GetStaticPadTemplates(GSTWStaticPadTemplate **staticTemplate)
{
    if(this->Factory == nullptr)
    {
        return false;
    }

    return this->Factory->GetStaticPadTemplates(staticTemplate);
}

void GSTWElement::ConnectToPadAddedSignal(GSTWPadAddedSignalHandler* handler)
{
    g_signal_connect(this->_GstElement, "pad-added", G_CALLBACK(gstw_pad_added_event), handler);
}

GSTWPadAddedSignalHandler::GSTWPadAddedSignalHandler()
{
    this->padFilter = nullptr;
}

GSTWPadAddedSignalHandler::~GSTWPadAddedSignalHandler()
{
    if(this->padFilter != nullptr)
    {
        delete this->padFilter;
        this->padFilter = nullptr;
    }
}

void GSTWPadAddedSignalHandler::UsePadFilter(GSTWPadFilter* padFilter)
{
    this->padFilter = padFilter;
}

void GSTWPadAddedSignalHandler::HandlePadAddedSignal(GstElement *gstElement, GstPad *gstPad)
{
    GSTWElement* element = new GSTWElement(gstElement);
    GSTWDynamicPad* pad = new GSTWDynamicPad(gstPad);

    if(this->padFilter != nullptr)
    {
        if(this->padFilter->Satisfies(pad))
        {
            this->OnHandlePadAddedSignal(element, pad);   
        }
    }
    else
    {
        this->OnHandlePadAddedSignal(element, pad);
    }
    
    delete pad;
    delete element;
}

static void gstw_pad_added_event(GstElement *element, GstPad *pad, GSTWPadAddedSignalHandler *handler)
{
    handler->HandlePadAddedSignal(element, pad);
}