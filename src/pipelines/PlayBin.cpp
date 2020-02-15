#include "gst/gst.h"
#include "PlayBin.h"

GSTWPlayBin::GSTWPlayBin(string friendlyName) : GSTWPipeline("playbin", friendlyName)
{
}

GSTWObjectProperties *GSTWPlayBin::Uri()
{
    if (this->uri == nullptr)
    {
        this->uri = new GSTWObjectProperties(this->_GstElement, "uri");
    }

    return this->uri;
}

GSTWPlayBin::~GSTWPlayBin()
{
    if (this->uri != nullptr)
    {
        delete this->uri;
        this->uri = nullptr;
    }
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
    handler->HandlePlayBinEvent(_gstPlayBin, stream);
}