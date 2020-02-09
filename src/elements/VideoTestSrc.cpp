#include "VideoTestSrc.h"

GSTWVideoTestSrc::GSTWVideoTestSrc(string friendlyName) : GSTWElement("videotestsrc", friendlyName)
{
    this->Pattern = new GSTWObjectProperties(this->_GstElement, "pattern");
}

GSTWVideoTestSrc::~GSTWVideoTestSrc()
{
    delete this->Pattern;
}