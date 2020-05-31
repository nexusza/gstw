#include "VideoTestSrc.h"

GSTWVideoTestSrc::GSTWVideoTestSrc(string friendlyName) : GSTWElement("videotestsrc", friendlyName)
{
}

void GSTWVideoTestSrc::SetPattern(int pattern)
{
    g_object_set(this->_GstElement, "pattern", pattern, NULL);
}

GSTWVideoTestSrc::~GSTWVideoTestSrc()
{
}