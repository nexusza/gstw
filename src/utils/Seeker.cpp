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

void GSTWSeeker::SeekSimple(int seconds)
{
    gst_element_seek_simple(this->Element->_GstElement, GST_FORMAT_TIME,
                            (GstSeekFlags)(GstSeekFlags::GST_SEEK_FLAG_FLUSH | GstSeekFlags::GST_SEEK_FLAG_KEY_UNIT), seconds * GST_SECOND);
}