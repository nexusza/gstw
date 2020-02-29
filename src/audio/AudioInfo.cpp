#include "AudioInfo.h"

GSTWAudioInfo::GSTWAudioInfo()
{
}

GSTWAudioInfo::~GSTWAudioInfo()
{
}

void GSTWAudioInfo::SetFormat(GstAudioFormat format, gint rate, gint channels, const GstAudioChannelPosition *position)
{
    gst_audio_info_set_format(&this->_GstAudioInfo, format, rate, channels, position);
}

GSTWCapabilities *GSTWAudioInfo::CreateAudioCaps()
{
    return new GSTWCapabilities(gst_audio_info_to_caps (&this->_GstAudioInfo));
}