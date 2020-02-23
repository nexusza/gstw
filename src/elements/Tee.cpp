#include "Tee.h"

GSTWTee::GSTWTee(string friendlyName) : GSTWElement("tee", friendlyName)
{
}

GSTWTee::~GSTWTee()
{
}

GSTWRequestPad* GSTWTee::GetNewSourcePad()
{
    return new GSTWRequestPad(this->_GstElement, "src_%u");
}

GSTWRequestPad* GSTWTee::LinkToElementSinkPad(GSTWElement* element)
{
    GSTWRequestPad* requestPad = this->GetNewSourcePad();
    GSTWStaticPad *sinkPad = element->GetSinkPad();

    requestPad->LinkPad(sinkPad);

    delete sinkPad;
    
    return requestPad;
}