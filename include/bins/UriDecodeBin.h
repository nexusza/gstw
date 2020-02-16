#include "gst/gst.h"
#include "Bin.h"
#include "ObjectProperties.h"

#ifndef GSTWURIDECODEBIN_H
#define GSTWURIDECODEBIN_H

class GSTWUriDecodeBin : public GSTWBin
{
public:
    GSTWUriDecodeBin(string friendlyName);
    ~GSTWUriDecodeBin();

    void SetUri(string uri);
};

#endif