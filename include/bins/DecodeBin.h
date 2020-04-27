#include "gst/gst.h"
#include "Bin.h"
#include "ObjectProperties.h"

#ifndef GSTWDECODEBIN_H
#define GSTWDECODEBIN_H

class GSTWDecodeBin : public GSTWBin
{
public:
    GSTWDecodeBin(string friendlyName);
    ~GSTWDecodeBin();
};

#endif