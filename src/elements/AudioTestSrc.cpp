#include "AudioTestSrc.h"

GSTWAudioTestSrc::GSTWAudioTestSrc(string friendlyName) : GSTWElement("audiotestsrc", friendlyName)
{
}

GSTWAudioTestSrc::~GSTWAudioTestSrc()
{
}

void GSTWAudioTestSrc::Freq(float value)
{
    g_object_set (this->_GstElement, "freq", value, NULL);
}