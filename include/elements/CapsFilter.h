#include "Element.h"

#ifndef GSTWCAPSFILTER_H
#define GSTWCAPSFILTER_H

class GSTWCapsFilter : public GSTWElement
{
private:
    /* data */
public:
    GSTWCapsFilter(string friendlyName);
    ~GSTWCapsFilter();
    void SetCapsFromString(string value);
};

#endif