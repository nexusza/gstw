#include "Element.h"
#include "LinkToSinkPadSignalHandler.h"

GSTWLinkToSinkPadSignalHandler::GSTWLinkToSinkPadSignalHandler(GSTWElement* element)
{
    this->element = element;
}

GSTWLinkToSinkPadSignalHandler::~GSTWLinkToSinkPadSignalHandler()
{
    this->element = nullptr;
}

void GSTWLinkToSinkPadSignalHandler::OnHandlePadAddedSignal(GSTWElement *element, GSTWDynamicPad* pad)
{
    if(!pad->IsLinked())
    {
        GSTWStaticPad *sinkPad = this->element->GetSinkStaticPad();

        pad->LinkPad(sinkPad);

        delete sinkPad;
    }    
}