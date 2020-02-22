#include "gst/gst.h"
#include <vector>

using namespace std;

#ifndef GSTWCAPABILITIES_H
#define GSTWCAPABILITIES_H

class GSTWCapabilities
{
public:
    GSTWCapabilities(GstCaps *_gstCaps);
    ~GSTWCapabilities();
    GstCaps *_GstCaps;
    gboolean IsAny();
    gboolean IsEmpty();
    vector<GstStructure*> GetGstStructures();
};

#endif
