#include "Pad.h"
#include "PadFilter.h"
#include "VideoPadFilter.h"
#include "AudioPadFilter.h"
#include "PadFeatureFilter.h"
#include "PadNameFilter.h"
#include "PadTypeFilter.h"

GSTWPadNameFilter::GSTWPadNameFilter(string padName)
{
    this->padName = padName;
}

bool GSTWPadNameFilter::Satisfies(GSTWPad* pad)
{
    return this->padName == pad->GetPadName();
}

GSTWPadTypeFilter::GSTWPadTypeFilter(string padType, bool startsWith)
{
    this->padType = padType;
    this->startsWith = startsWith;
}

bool GSTWPadTypeFilter::Satisfies(GSTWPad* pad)
{
    if(startsWith)
    {
        return pad->GetPadType().rfind(this->padType, 0) == 0;
    }
    return this->padType == pad->GetPadType();
}

GSTWPadFeatureFilter::GSTWPadFeatureFilter(string padFeature)
{
    this->padFeature = padFeature;
}

bool GSTWPadFeatureFilter::Satisfies(GSTWPad* pad)
{
    return pad->HasFeature(padFeature);
}

void GSTWPadFilter::AddFilter(GSTWPadFilterType *filter)
{
    this->filters.push_back(filter);
}

bool GSTWPadFilter::Satisfies(GSTWPad* pad)
{
    int filterSize = this->filters.size();

    if(filterSize == 0)
    {
        return false;
    }

    for (int index = 0; index < filterSize; index++)
    {
        GSTWPadFilterType *filter = this->filters[index];
        if(!filter->Satisfies(pad))
        {
            return false;
        }
    }
    
    return true;
}

GSTWVideoPadFilter::GSTWVideoPadFilter()
{
    this->AddFilter(new GSTWPadTypeFilter("video", true));
}

GSTWAudioPadFilter::GSTWAudioPadFilter()
{
    this->AddFilter(new GSTWPadTypeFilter("audio", true));
}