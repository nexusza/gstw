#include "VideoTestSrc.h"

GSTWVideoTestSrc::GSTWVideoTestSrc(string friendlyName) : GSTWElement("videotestsrc", friendlyName)
{
    
}

GSTWObjectProperties* GSTWVideoTestSrc::Pattern()
{
    if(this->pattern == nullptr)
    {
        this->pattern = new GSTWObjectProperties(this->_GstElement, "pattern");
    }

    return this->pattern;
}

GSTWVideoTestSrc::~GSTWVideoTestSrc()
{
    if(this->pattern != nullptr)
    {
        delete this->pattern;
        this->pattern = nullptr;
    }    
}