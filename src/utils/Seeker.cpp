#include "Element.h"
#include "Seeker.h"

GSTWSeeker::GSTWSeeker(GSTWElement *element)
{
    this->Element = element;
}

GSTWSeeker::~GSTWSeeker()
{
    this->Element = nullptr;
}

gboolean GSTWSeeker::QueryStartAndEnd(gint64 *start, gint64 *end)
{
    gboolean canSeek;

    GstQuery *query = gst_query_new_seeking(GST_FORMAT_TIME);
    if (gst_element_query(this->Element->_GstElement, query))
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

gboolean GSTWSeeker::QueryDuration(gint64 *duration)
{
    if (!gst_element_query_duration(this->Element->_GstElement, GST_FORMAT_TIME, duration))
    {
        g_printerr("Could not query current duration.\n");
        return false;
    }
    return true;
}

gboolean GSTWSeeker::QueryPosition(gint64 *position)
{
    if (!gst_element_query_position(this->Element->_GstElement, GST_FORMAT_TIME, position))
    {
        g_printerr("Could not query current position.\n");
        return false;
    }

    return true;
}

gboolean GSTWSeeker::SeekSimple(gint64 seconds)
{
    return gst_element_seek_simple(this->Element->_GstElement, GST_FORMAT_TIME,
                                   (GstSeekFlags)(GstSeekFlags::GST_SEEK_FLAG_FLUSH | GstSeekFlags::GST_SEEK_FLAG_KEY_UNIT), seconds * GST_SECOND);
}

gboolean GSTWSeeker::SeekForward(gdouble rate)
{
    gint64 position;

    if (this->QueryPosition(&position))
    {
        GstEvent *seek_event = gst_event_new_seek(rate, GST_FORMAT_TIME,
                                                  (GstSeekFlags)(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE), GST_SEEK_TYPE_SET,
                                                  position, GST_SEEK_TYPE_END, 0);

        gboolean result = gst_element_send_event(this->Element->_GstElement, seek_event);

        if (!result)
        {
            g_print("Seek Forward failed: %g\n", rate);
        }

        return result;
    }

    return false;
}

gboolean GSTWSeeker::SeekBackward(gdouble rate)
{
    gint64 position;

    if (this->QueryPosition(&position))
    {
        GstEvent *seek_event = gst_event_new_seek(rate, GST_FORMAT_TIME,
                                                  (GstSeekFlags)(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE), GST_SEEK_TYPE_SET, 0,
                                                  GST_SEEK_TYPE_SET, position);

        gboolean result = gst_element_send_event(this->Element->_GstElement, seek_event);

        if (!result)
        {
            g_print("Seek Backward failed: %g\n", rate);
        }

        return result;
    }

    return false;
}

gboolean GSTWSeeker::StepFrame(gdouble rate)
{
    GstEvent *step_event = gst_event_new_step(GST_FORMAT_BUFFERS, 1, rate, TRUE, FALSE);

    gboolean result = gst_element_send_event(this->Element->_GstElement, step_event);

    if (!result)
    {
        g_print("Step Frame failed: %g\n", rate);
    }

    return result;
}