#include "gst/gst.h"
#include "Element.h"
#include "ObjectProperties.h"

#ifndef GSTWPLAYBIN_H
#define GSTWPLAYBIN_H

class GSTWPlayBin : public GSTWElement
{
private:
    /* data */
public:
    GSTWPlayBin(string friendlyName);
    ~GSTWPlayBin();

    GSTWObjectProperties* Uri;
};

#endif