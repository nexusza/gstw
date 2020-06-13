#include "Pad.h"
#include "PadFilter.h"

#ifndef GSTWPADTYPEFILTER_H
#define GSTWPADTYPEFILTER_H

class GSTWPadTypeFilter : public GSTWPadFilterType
{
private:
    string padType;
    bool startsWith;
public:
    GSTWPadTypeFilter(string padType, bool startsWith);
    bool Satisfies(GSTWPad* pad);
};

#endif