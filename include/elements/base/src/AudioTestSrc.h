#include "Element.h"
#include "ObjectProperties.h"

#ifndef GSTWAUDIOTESTSRC_H
#define GSTWAUDIOTESTSRC_H

class GSTWAudioTestSrc : public GSTWElement
{
public:
    GSTWAudioTestSrc(string friendlyName);
    ~GSTWAudioTestSrc();
    void Freq(float value);
};

#endif
