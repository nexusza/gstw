#include "gst/gst.h"
#include "Bin.h"

#ifndef GSTWCUSTOMBIN_H
#define GSTWCUSTOMBIN_H

class GSTWCustomBin : public GSTWBin
{
public:
    GSTWCustomBin(string friendlyName);
    ~GSTWCustomBin();
    void CreateElement();
};

#endif