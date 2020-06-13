#include "Pad.h"
#include "PadFilter.h"

#ifndef GSTWPADFEATUREFILTER_H
#define GSTWPADFEATUREFILTER_H

class GSTWPadFeatureFilter : public GSTWPadFilterType
{
private:
    string padFeature;
public:
    GSTWPadFeatureFilter(string padFeature);
    bool Satisfies(GSTWPad* pad);
};

#endif