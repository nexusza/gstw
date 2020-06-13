#include "Pad.h"

#ifndef GSTWPADFILTER_H
#define GSTWPADFILTER_H

class GSTWPadFilterType
{
public:
    virtual bool Satisfies(GSTWPad* pad) = 0;
};

class GSTWPadFilter
{
private:
    vector<GSTWPadFilterType*> filters;
public:
    void AddFilter(GSTWPadFilterType* filter);
    virtual bool Satisfies(GSTWPad* pad);
};

#endif