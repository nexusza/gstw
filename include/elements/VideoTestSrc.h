#include "Element.h"
#include "ObjectProperties.h"

#ifndef GSTWVIDEOTESTSRC_H
#define GSTWVIDEOTESTSRC_H

class GSTWVideoTestSrc : public GSTWElement
{
private:
    /* data */
public:
    GSTWVideoTestSrc(string friendlyName);
    ~GSTWVideoTestSrc();

    GSTWObjectProperties* Pattern;
};

#endif
