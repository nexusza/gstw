#include "gst/gst.h"
#include "Pipeline.h"
#include "ObjectProperties.h"

#ifndef GSTWPLAYBIN_H
#define GSTWPLAYBIN_H

class GSTWPlayBinTagsChangedEventHandler
{
private:
    /* data */
public:
    GSTWPlayBinTagsChangedEventHandler(/* args */);
    ~GSTWPlayBinTagsChangedEventHandler();
    virtual void HandlePlayBinEvent(GstElement *_gstPlayBin, gint stream) = 0;
};

class GSTWPlayBin : public GSTWPipeline
{
private:
    GSTWObjectProperties* uri;
public:
    GSTWPlayBin(string friendlyName);
    ~GSTWPlayBin();

    GSTWObjectProperties* Uri();

    void OnVideoTagsChanged(GSTWPlayBinTagsChangedEventHandler* handler);
    void OnAudioTagsChanged(GSTWPlayBinTagsChangedEventHandler* handler);
    void OnTextTagsChanged(GSTWPlayBinTagsChangedEventHandler* handler);
};

static void playbin_tags_changed (GstElement *_gstPlayBin, gint stream, GSTWPlayBinTagsChangedEventHandler *handler);

#endif