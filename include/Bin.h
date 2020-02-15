#include "Element.h"

#ifndef GSTWBIN_H
#define GSTWBIN_H

class GSTWBin : public GSTWElement
{
private:
    /* data */
public:
    GSTWBin(string elementName, string friendlyName);
    ~GSTWBin();

    void AddElement(GSTWElement* element);
};

#endif