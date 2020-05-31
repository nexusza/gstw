#include "gst/gst.h"
#include "Element.h"

#ifndef GSTWSOUPHTTPSRC_H
#define GSTWSOUPHTTPSRC_H

class GSTWSoupHttpSrc : public GSTWElement
{
private:
    /* data */
public:
    GSTWSoupHttpSrc(string friendlyName);
    ~GSTWSoupHttpSrc();
    void SetLocation(string value);
};

#endif