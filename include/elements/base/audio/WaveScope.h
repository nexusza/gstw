#include "Element.h"

#ifndef GSTWWAVESCOPE_H
#define GSTWWAVESCOPE_H

class GSTWWaveScope : public GSTWElement
{
private:
    /* data */
public:
    GSTWWaveScope(string friendlyName);
    ~GSTWWaveScope();
    void Shader(int value);
    void Style(int value);
};

#endif