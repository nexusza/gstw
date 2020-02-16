#include "gst/gst.h"

#ifndef GSTWSEEKQUERY_H
#define GSTWSEEKQUERY_H

class GSTWSeekQuery
{
private:
    /* data */
public:
    GSTWSeekQuery();
    ~GSTWSeekQuery();

    gboolean QueryStartAndEnd(GstElement *_gstElemenet, gint64 *start, gint64 *end);
    gboolean QueryDuration(GstElement *_gstElemenet, gint64 *duration);
    gboolean QueryCurrent(GstElement *_gstElement, gint64 *current);
};

#endif