#include "Element.h"

#ifndef GSTWAUDIORESAMPLE_H
#define GSTWAUDIORESAMPLE_H

class GSTWAudioResample : public GSTWElement
{
private:
    /* data */
public:
    GSTWAudioResample(string friendlyName);
    ~GSTWAudioResample();
};

#endif