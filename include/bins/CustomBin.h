#include "gst/gst.h"
#include "Pad.h"
#include "Bin.h"

#ifndef GSTWCUSTOMBIN_H
#define GSTWCUSTOMBIN_H

class GSTWCustomBin : public GSTWBin
{
public:
    GSTWCustomBin(string friendlyName);
    ~GSTWCustomBin();
    void CreateElement();
    void LinkSrcGhostPad(GSTWPad* pad);
    void AddSrcGhostPad();
};

#endif