//#include <string.h>
#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include "All.h"

#include <gdk/gdk.h>
#if defined(GDK_WINDOWING_X11)
#include <gdk/gdkx.h>
#elif defined(GDK_WINDOWING_WIN32)
#include <gdk/gdkwin32.h>
#elif defined(GDK_WINDOWING_QUARTZ)
#include <gdk/gdkquartz.h>
#endif

class MyCustomData : public GSTWBusMessageHandler, public GSTWPlayBinTagsChangedEventHandler
{
public:

    GtkWidget *slider;              /* Slider widget to keep track of current position */
    GtkWidget *streams_list;        /* Text widget to display info about the streams */
    gulong slider_update_signal_id; /* Signal ID for the slider update signal */
    GstState state;                 /* Current state of the pipeline */
    gint64 duration;                /* Duration of the clip, in nanoseconds */
    //GSTWPlayBin *playbin;
    GSTWCustomPipeline *playbin;

    void HandlePlayBinEvent(GstElement *_gstPlayBin, gint stream)
    {
    
    }

    void OnHandleStateChanged(GSTWMessage *message)
    {
    }

    void OnHandleApplication(GSTWMessage *message)
    {
    }

    void OnHandleEOS(GSTWMessage *message)
    {
    }

    void OnHandleError(GSTWMessage *message)
    {
    }
};

static gboolean refresh_ui(MyCustomData *data)
{
}

int main(int argc, char *argv[])
{
    MyCustomData data;
    GstStateChangeReturn ret;
    //GstBus *bus;

    /* Initialize GTK */
    gtk_init(&argc, &argv);

    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    /* Initialize our data structure */
    //memset(&data, 0, sizeof(data));
    data.duration = GST_CLOCK_TIME_NONE;

    /* Create the elements */
    //data.playbin = new GSTWPlayBin("playbin");
    data.playbin = new GSTWCustomPipeline("playbin");
    GSTWMessageLogger *logger = new GSTWMessageLogger(data.playbin);
    GSTWAutoVideoSink *sink = new GSTWAutoVideoSink("sink");
    GSTWVideoTestSrc *src = new GSTWVideoTestSrc("testsrc");

    data.playbin->CreateElement();

    data.playbin->AddElement(src);
    data.playbin->AddElement(sink);

    src->Link(sink);

    src->Pattern()->Set(0);

    /* Set the URI to play */
    //data.playbin->Uri()->Set("https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm");
    //
    //data.playbin->OnVideoTagsChanged(&data);
    //data.playbin->OnAudioTagsChanged(&data);
    //data.playbin->OnTextTagsChanged(&data);

    GSTWBus *bus = data.playbin->GetBus();

    bus->AddMessageHandler(logger);
    bus->AddMessageHandler(&data);

    bus->BeginWatch();

    data.playbin->Play();

    /* Register a function that GLib will call every second */
    g_timeout_add_seconds(1, (GSourceFunc)refresh_ui, &data);
    //
    ///* Start the GTK main loop. We will not regain control until gtk_main_quit is called. */
    gtk_main();

    data.playbin->Stop();

    delete logger;

    delete bus;

    delete data.playbin;

    return 0;
}