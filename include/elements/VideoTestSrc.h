#include "Element.h"
#include "ObjectProperties.h"

#ifndef GSTWVIDEOTESTSRC_H
#define GSTWVIDEOTESTSRC_H

class GSTWVideoTestSrc : public GSTWElement
{
public:
    GSTWVideoTestSrc(string friendlyName);
    ~GSTWVideoTestSrc();

    void SetPattern(int pattern);
};

#endif
