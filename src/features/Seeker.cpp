#include "MessageHandler.h"
#include "Seeker.h"
#include "SeekQuery.h"

GSTWSeeker::GSTWSeeker(GSTWElement *element) : GSTWMessageHandler()
{
    this->Element = element;
    this->CanSeek = false;
    this->SeekDone = false;
}

GSTWSeeker::~GSTWSeeker()
{
}

void GSTWSeeker::OnHandleDurationChange(GSTWMessage *message)
{
    this->CanSeek = false;
}

void GSTWSeeker::OnHandleStateChanged(GSTWMessage *message)
{
    if (message->IsForElement(this->Element->_GstElement))
    {
        if (message->IsPlaying())
        {
            GSTWSeekQuery query;
            this->CanSeek = query.QuerySeekRange(this->Element->_GstElement, &this->Start, &this->End, &this->Duration);
        }
        else
        {
            this->CanSeek = false;
        }
    }
}

void GSTWSeeker::OnHandleTimeout()
{
    if (!this->CanSeek)
    {
        return;
    }

    GSTWSeekQuery query;

    gint64 current = query.QueryCurrent(this->Element->_GstElement);

    /* Print current position and total duration */
    g_print("Position %" GST_TIME_FORMAT " / %" GST_TIME_FORMAT "\r",
            GST_TIME_ARGS(current), GST_TIME_ARGS(this->Duration));

    /* If seeking is enabled, we have not done it yet, and the time is right, seek */
    if (this->CanSeek && !this->SeekDone && current > 10 * GST_SECOND)
    {
        g_print("\nReached 10s, performing seek...\n");
        gst_element_seek_simple(this->Element->_GstElement, GST_FORMAT_TIME,
                                (GstSeekFlags)(GstSeekFlags::GST_SEEK_FLAG_FLUSH | GstSeekFlags::GST_SEEK_FLAG_KEY_UNIT), 30 * GST_SECOND);
        this->SeekDone = true;
    }
}