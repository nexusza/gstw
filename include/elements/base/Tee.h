#include "Element.h"
#include "RequestPad.h"

#ifndef GSTWTEE_H
#define GSTWTEE_H

class GSTWTee : public GSTWElement
{
private:
    /* data */
public:
    GSTWTee(string friendlyName);
    ~GSTWTee();
    GSTWRequestPad* LinkToElementSinkPad(GSTWElement* element);
};

#endif