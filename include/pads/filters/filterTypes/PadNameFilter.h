#include "Pad.h"
#include "PadFilter.h"

#ifndef GSTWPADNAMEFILTER_H
#define GSTWPADNAMEFILTER_H

class GSTWPadNameFilter : public GSTWPadFilterType
{
private:
    string padName;
public:
    GSTWPadNameFilter(string padName);
    bool Satisfies(GSTWPad* pad);
};

#endif