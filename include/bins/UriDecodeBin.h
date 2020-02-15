#include "gst/gst.h"
#include "Bin.h"
#include "ObjectProperties.h"

#ifndef GSTWURIDECODEBIN_H
#define GSTWURIDECODEBIN_H

class GSTWUriDecodeBin : public GSTWBin
{
private:
    GSTWObjectProperties* uri;
public:
    GSTWUriDecodeBin(string friendlyName);
    ~GSTWUriDecodeBin();

    GSTWObjectProperties* Uri();
};

#endif