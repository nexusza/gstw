#include "SeekQuery.h"

GSTWSeekQuery::GSTWSeekQuery()
{
}

GSTWSeekQuery::~GSTWSeekQuery()
{
}

gboolean GSTWSeekQuery::QueryStartAndEnd(GstElement *_gstElemenet, gint64 *start, gint64 *end)
{
    gboolean canSeek;

    GstQuery *query = gst_query_new_seeking(GST_FORMAT_TIME);
    if (gst_element_query(_gstElemenet, query))
    {
        gst_query_parse_seeking(query, NULL, &canSeek, start, end);

        if (!canSeek)
        {
            g_print("Seeking is DISABLED for this stream.\n");
        }
    }
    else
    {
        g_printerr("Seeking query failed.");
    }

    gst_query_unref(query);

    return canSeek;
}

gboolean GSTWSeekQuery::QueryDuration(GstElement *_gstElemenet, gint64 *duration)
{
    if (!gst_element_query_duration(_gstElemenet, GST_FORMAT_TIME, duration))
    {
        g_printerr("Could not query current duration.\n");
        return false;
    }
    return true;
}

gboolean GSTWSeekQuery::QueryCurrent(GstElement *_gstElement, gint64 *current)
{
    if (!gst_element_query_position(_gstElement, GST_FORMAT_TIME, current))
    {
        g_printerr("Could not query current position.\n");
        return false;
    }

    return true;
}