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

    gboolean QueryStartAndEnd(gint64 *start, gint64 *end);
    gboolean QueryDuration(gint64 *duration);
    gboolean QueryPosition(gint64 *position);
    
    gboolean SeekSimple(gint64 seconds);
    gboolean SeekForward(gdouble rate);
    gboolean SeekBackward(gdouble rate);
    gboolean StepFrame(gdouble rate);

    GSTWElement* Element;
};


#endif