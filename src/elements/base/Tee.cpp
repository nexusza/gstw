#include "Tee.h"

GSTWTee::GSTWTee(string friendlyName) : GSTWElement("tee", friendlyName)
{
}

GSTWTee::~GSTWTee()
{
}

GSTWRequestPad* GSTWTee::LinkToElementSinkPad(GSTWElement* element)
{
    GSTWRequestPad* requestPad = this->GetSrcRequestPad(0);
    GSTWStaticPad *sinkPad = element->GetSinkStaticPad();

    requestPad->LinkPad(sinkPad);

    delete sinkPad;
    
    return requestPad;
}