#include "gst/gst.h"
#include "Pipeline.h"
#include "ObjectProperties.h"
#include <vector>

using namespace std;

#ifndef GSTWPLAYBIN_H
#define GSTWPLAYBIN_H

class GSTWPlayBinTagsChangedEventHandler
{
private:
    /* data */
public:
    GSTWPlayBinTagsChangedEventHandler(/* args */);
    ~GSTWPlayBinTagsChangedEventHandler();
    virtual void HandlePlayBinTagsChanged(GstElement *_gstPlayBin, gint stream) = 0;
};

struct VideoTags
{
    string Codec;
    int StreamIndex;
};

struct AudioTags
{
    string Codec;
    string Language;
    guint Bitrate;
    int StreamIndex;
};

struct SubtitleTags
{
    string Language;
    int StreamIndex;
};

//docs: https://gstreamer.freedesktop.org/documentation/playback/playbin.html?gi-language=c
class GSTWPlayBin : public GSTWPipeline
{
public:
    GSTWPlayBin(string friendlyName);
    ~GSTWPlayBin();

    vector<VideoTags> GetVideoTags();
    vector<AudioTags> GetAudioTags();
    vector<SubtitleTags> GetSubtitleTags();
    void SetUri(string uri);
    GSTWElement *GetAudioSink();
    GSTWElement *GetVideoSink();
    gint GetNumberOfVideoStreams();
    gint GetNumberOfAudioStreams();
    gint GetNumberOfSubtitleStreams();
    void OnVideoTagsChanged(GSTWPlayBinTagsChangedEventHandler *handler);
    void OnAudioTagsChanged(GSTWPlayBinTagsChangedEventHandler *handler);
    void OnTextTagsChanged(GSTWPlayBinTagsChangedEventHandler *handler);
};

static void playbin_tags_changed(GstElement *_gstPlayBin, gint stream, GSTWPlayBinTagsChangedEventHandler *handler);

#endif