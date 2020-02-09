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

    gboolean QuerySeekRange(GstElement* _gstElemenet, gint64* start, gint64* end, gint64* durection);
    gint64 QueryCurrent(GstElement* _gstElemenet);
};

#endif