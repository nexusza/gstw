#include "gst/gst.h"

#ifndef GSTWSEEKER_H
#define GSTWSEEKER_H

class GSTWSeeker
{
private:
    /* data */
public:
    GSTWSeeker(GSTWElement* element);
    ~GSTWSeeker();

    void SeekSimple(int seconds);

    GSTWElement* Element;
};


#endif