#include "gst/gst.h"
#include "PlayBin.h"

GSTWPlayBin::GSTWPlayBin(string friendlyName) : GSTWPipeline("playbin", friendlyName)
{
}

void GSTWPlayBin::SetUri(string uri)
{
    g_object_set(this->_GstElement, "uri", uri.c_str(), NULL);
}

GSTWPlayBin::~GSTWPlayBin()
{
}

vector<VideoTags> GSTWPlayBin::GetVideoTags()
{
    int streams = this->GetNumberOfVideoStreams();
    gchar *str;
    GstTagList *tags;
    vector<VideoTags> result;

    for (int i = 0; i < streams; i++)
    {
        tags = NULL;

        g_signal_emit_by_name(this->_GstElement, "get-video-tags", i, &tags);

        if (tags)
        {
            string codecValue;

            if(gst_tag_list_get_string(tags, GST_TAG_VIDEO_CODEC, &str))
            {
                codecValue = str;
                g_free(str);
            }

            result.push_back({codecValue, i});

            gst_tag_list_free(tags);
        }
    }

    return result;
}

vector<AudioTags> GSTWPlayBin::GetAudioTags()
{
    int streams = this->GetNumberOfAudioStreams();
    gchar *str;
    guint bitRate;
    GstTagList *tags;
    vector<AudioTags> result;

    for (int i = 0; i < streams; i++)
    {
        tags = NULL;

        g_signal_emit_by_name(this->_GstElement, "get-audio-tags", i, &tags);

        if (tags)
        {
            string codecValue;
            string languageValue;
            guint bitRateValue;

            if(gst_tag_list_get_string(tags, GST_TAG_AUDIO_CODEC, &str))
            {
                codecValue = str;
                g_free(str);
            }

            if(gst_tag_list_get_string(tags, GST_TAG_LANGUAGE_CODE, &str))
            {
                languageValue = str;
                g_free(str);
            }

            if(gst_tag_list_get_uint(tags, GST_TAG_BITRATE, &bitRate))
            {
                bitRateValue = bitRate;
            }

            result.push_back({codecValue, languageValue, bitRateValue, i});
            
            gst_tag_list_free(tags);
        }
    }

    return result;
}

vector<SubtitleTags> GSTWPlayBin::GetSubtitleTags()
{
    int streams = this->GetNumberOfAudioStreams();
    gchar *str;
    GstTagList *tags;
    vector<SubtitleTags> result;

    for (int i = 0; i < streams; i++)
    {
        tags = NULL;

        g_signal_emit_by_name(this->_GstElement, "get-text-tags", i, &tags);

        if (tags)
        {
            string languageValue;
            if(gst_tag_list_get_string(tags, GST_TAG_LANGUAGE_CODE, &str))
            {
                languageValue = str;
                g_free(str);
            }

            result.push_back({languageValue, i});

            gst_tag_list_free(tags);
        }
    }

    return result;
}

gint GSTWPlayBin::GetNumberOfVideoStreams()
{
    gint value;
    g_object_get(this->_GstElement, "n-video", &value, NULL);
    return value;
}

gint GSTWPlayBin::GetNumberOfAudioStreams()
{
    gint value;
    g_object_get(this->_GstElement, "n-audio", &value, NULL);
    return value;
}

gint GSTWPlayBin::GetNumberOfSubtitleStreams()
{
    gint value;
    g_object_get(this->_GstElement, "n-text", &value, NULL);
    return value;
}

void GSTWPlayBin::OnVideoTagsChanged(GSTWPlayBinTagsChangedEventHandler *handler)
{
    g_signal_connect(G_OBJECT(this->_GstElement), "video-tags-changed", (GCallback)playbin_tags_changed, handler);
}

void GSTWPlayBin::OnAudioTagsChanged(GSTWPlayBinTagsChangedEventHandler *handler)
{
    g_signal_connect(G_OBJECT(this->_GstElement), "audio-tags-changed", (GCallback)playbin_tags_changed, handler);
}

void GSTWPlayBin::OnTextTagsChanged(GSTWPlayBinTagsChangedEventHandler *handler)
{
    g_signal_connect(G_OBJECT(this->_GstElement), "text-tags-changed", (GCallback)playbin_tags_changed, handler);
}

GSTWPlayBinTagsChangedEventHandler::GSTWPlayBinTagsChangedEventHandler(/* args */)
{
}

GSTWPlayBinTagsChangedEventHandler::~GSTWPlayBinTagsChangedEventHandler()
{
}

static void playbin_tags_changed(GstElement *_gstPlayBin, gint stream, GSTWPlayBinTagsChangedEventHandler *handler)
{
    handler->HandlePlayBinTagsChanged(_gstPlayBin, stream);
}