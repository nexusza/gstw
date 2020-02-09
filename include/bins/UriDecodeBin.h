#include "gst/gst.h"
#include "Element.h"
#include "ObjectProperties.h"

#ifndef GSTWURIDECODEBIN_H
#define GSTWURIDECODEBIN_H

class GSTWUriDecodeBin : public GSTWElement
{
private:
    /* data */
public:
    GSTWUriDecodeBin(string friendlyName);
    ~GSTWUriDecodeBin();

    GSTWObjectProperties* Uri;
};

#endif