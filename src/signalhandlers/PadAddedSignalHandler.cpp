#include "Element.h"
#include "PadAddedSignalHandler.h"

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

void GSTWPadAddedSignalHandler::ConnectToSignal(GSTWElement* element)
{
    g_signal_connect(element->_GstElement, "pad-added", G_CALLBACK(gstw_pad_added_signal), this);
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
        else
        {
            g_print("PadFilter failed to satisfy padd-added signal for pad '%s', pad type '%s' and element '%s'\n", pad->GetPadName().c_str(), pad->GetPadType().c_str(), element->GetName().c_str());
        }
    }
    else
    {
        this->OnHandlePadAddedSignal(element, pad);
    }
    
    delete pad;
    delete element;
}

static void gstw_pad_added_signal(GstElement *element, GstPad *pad, GSTWPadAddedSignalHandler *handler)
{
    handler->HandlePadAddedSignal(element, pad);
}