#include "Pad.h"

#ifndef GSTWPADFILTER_H
#define GSTWPADFILTER_H

class GSTWPadFilter
{
private:
    string padNameFilter;
    string padTypeFilter;
public:
    void FilterByPadName(string padName);
    void FilterByPadType(string padType);
    virtual bool Satisfies(GSTWPad* pad);
};

class GSTWVideoPadFilter : public GSTWPadFilter
{
public:
    GSTWVideoPadFilter();
};

class GSTWAudioPadFilter : public GSTWPadFilter
{
public:
    GSTWAudioPadFilter();
};

#endif