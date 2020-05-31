#include "Pad.h"
#include "PadFilter.h"

void GSTWPadFilter::FilterByPadName(string padName)
{
    this->padNameFilter = padName;
}

void GSTWPadFilter::FilterByPadType(string padType)
{
    this->padTypeFilter = padType;
}

bool GSTWPadFilter::Satisfies(GSTWPad* pad)
{
    if(!this->padNameFilter.empty())
    {
        return this->padNameFilter == pad->GetPadName();
    }
    else if(!this->padTypeFilter.empty())
    {
        return this->padTypeFilter == pad->GetPadName();
    }
    
    return false;
}

GSTWVideoPadFilter::GSTWVideoPadFilter()
{
    this->FilterByPadName("video_0");
}

GSTWAudioPadFilter::GSTWAudioPadFilter()
{
    this->FilterByPadName("audio_0");
}