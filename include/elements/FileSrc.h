#include "gst/gst.h"
#include "Element.h"

#ifndef GSTWFILESRC_H
#define GSTWFILESRC_H

class GSTWFileSrc : public GSTWElement
{
private:
    /* data */
public:
    GSTWFileSrc(string friendlyName);
    ~GSTWFileSrc();
    void SetLocation(string value);
};

#endif