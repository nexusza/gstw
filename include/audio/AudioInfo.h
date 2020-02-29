#include "gst/audio/audio.h"
#include "Capabilities.h"

#ifndef GSTWAUDIOINFO_H
#define GSTWAUDIOINFO_H

class GSTWAudioInfo
{
private:
    /* data */
public:
    GSTWAudioInfo();
    ~GSTWAudioInfo();
    GstAudioInfo _GstAudioInfo;
    void SetFormat(GstAudioFormat format, gint rate, gint channels, const GstAudioChannelPosition *position);
    GSTWCapabilities *CreateAudioCaps();
};

#endif