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

class MyCustomData;

static gboolean refresh_ui(MyCustomData *data);
static void analyze_streams(MyCustomData *data);

class MyCustomData : public GSTWBusMessageHandler, public GSTWPlayBinTagsChangedEventHandler
{
public:
    GtkWidget *slider;              /* Slider widget to keep track of current position */
    GtkWidget *streams_list;        /* Text widget to display info about the streams */
    gulong slider_update_signal_id; /* Signal ID for the slider update signal */
    GstState state;                 /* Current state of the pipeline */
    gint64 duration;                /* Duration of the clip, in nanoseconds */
    GSTWPlayBin *playbin;

    void HandlePlayBinTagsChanged(GstElement *_gstPlayBin, gint stream)
    {
        this->playbin->SendApplicationMessage("tags-changed");
    }

    void OnHandleStateChanged(GstBus *_gstBus, GSTWMessage *message)
    {
        if (message->IsForElement(this->playbin))
        {
            this->state = message->NewState;

            if (message->OldState == GstState::GST_STATE_READY && this->state == GstState::GST_STATE_PAUSED)
            {
                refresh_ui(this);
            }
        }
    }

    void OnHandleApplication(GstBus *_gstBus, GSTWMessage *message)
    {
        if (message->GetMessageName() == "tags-changed")
        {
            analyze_streams(this);
        }
    }

    void OnHandleEOS(GstBus *_gstBus, GSTWMessage *message)
    {
        this->playbin->SetToReadyState();
    }

    void OnHandleError(GstBus *_gstBus, GSTWMessage *message)
    {
        this->playbin->SetToReadyState();
    }
};

static void realize_cb(GtkWidget *widget, MyCustomData *data)
{
    GdkWindow *window = gtk_widget_get_window(widget);
    guintptr window_handle;

    if (!gdk_window_ensure_native(window))
        g_error("Couldn't create native window needed for GstVideoOverlay!");

        /* Retrieve window handler from GDK */
#if defined(GDK_WINDOWING_WIN32)
    window_handle = (guintptr)GDK_WINDOW_HWND(window);
#elif defined(GDK_WINDOWING_QUARTZ)
    window_handle = gdk_quartz_window_get_nsview(window);
#elif defined(GDK_WINDOWING_X11)
    window_handle = GDK_WINDOW_XID(window);
#endif
    /* Pass it to playbin, which implements VideoOverlay and will forward it to the video sink */
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(data->playbin->_GstElement), window_handle);
}

/* This function is called when the PLAY button is clicked */
static void play_cb(GtkButton *button, MyCustomData *data)
{
    data->playbin->SetToPlayingState();
}

/* This function is called when the PAUSE button is clicked */
static void pause_cb(GtkButton *button, MyCustomData *data)
{
    data->playbin->SetToPausedState();
}

/* This function is called when the STOP button is clicked */
static void stop_cb(GtkButton *button, MyCustomData *data)
{
    data->playbin->SetToReadyState();
}

/* This function is called when the main window is closed */
static void delete_event_cb(GtkWidget *widget, GdkEvent *event, MyCustomData *data)
{
    stop_cb(NULL, data);
    gtk_main_quit();
}

/* This function is called everytime the video window needs to be redrawn (due to damage/exposure,
 * rescaling, etc). GStreamer takes care of this in the PAUSED and PLAYING states, otherwise,
 * we simply draw a black rectangle to avoid garbage showing up. */
static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, MyCustomData *data)
{
    if (data->state < GST_STATE_PAUSED)
    {
        GtkAllocation allocation;

        /* Cairo is a 2D graphics library which we use here to clean the video window.
     * It is used by GStreamer for other reasons, so it will always be available to us. */
        gtk_widget_get_allocation(widget, &allocation);
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_rectangle(cr, 0, 0, allocation.width, allocation.height);
        cairo_fill(cr);
    }

    return FALSE;
}

/* This function is called when the slider changes its position. We perform a seek to the
 * new position here. */
static void slider_cb(GtkRange *range, MyCustomData *data)
{
    gdouble value = gtk_range_get_value(GTK_RANGE(data->slider));
    GSTWSeeker seeker = {data->playbin};
    seeker.SeekSimple(value);
}

/* This creates all the GTK+ widgets that compose our application, and registers the callbacks */
static void create_ui(MyCustomData *data)
{
    GtkWidget *main_window;                              /* The uppermost window, containing all other windows */
    GtkWidget *video_window;                             /* The drawing area where the video will be shown */
    GtkWidget *main_box;                                 /* VBox to hold main_hbox and the controls */
    GtkWidget *main_hbox;                                /* HBox to hold the video_window and the stream info text widget */
    GtkWidget *controls;                                 /* HBox to hold the buttons and the slider */
    GtkWidget *play_button, *pause_button, *stop_button; /* Buttons */

    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(main_window), "delete-event", G_CALLBACK(delete_event_cb), data);

    video_window = gtk_drawing_area_new();
    G_GNUC_BEGIN_IGNORE_DEPRECATIONS
    gtk_widget_set_double_buffered(video_window, FALSE);
    G_GNUC_BEGIN_IGNORE_DEPRECATIONS
    g_signal_connect(video_window, "realize", G_CALLBACK(realize_cb), data);
    g_signal_connect(video_window, "draw", G_CALLBACK(draw_cb), data);

    play_button = gtk_button_new_from_icon_name("media-playback-start", GTK_ICON_SIZE_SMALL_TOOLBAR);
    g_signal_connect(G_OBJECT(play_button), "clicked", G_CALLBACK(play_cb), data);

    pause_button = gtk_button_new_from_icon_name("media-playback-pause", GTK_ICON_SIZE_SMALL_TOOLBAR);
    g_signal_connect(G_OBJECT(pause_button), "clicked", G_CALLBACK(pause_cb), data);

    stop_button = gtk_button_new_from_icon_name("media-playback-stop", GTK_ICON_SIZE_SMALL_TOOLBAR);
    g_signal_connect(G_OBJECT(stop_button), "clicked", G_CALLBACK(stop_cb), data);

    data->slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
    gtk_scale_set_draw_value(GTK_SCALE(data->slider), 0);
    data->slider_update_signal_id = g_signal_connect(G_OBJECT(data->slider), "value-changed", G_CALLBACK(slider_cb), data);

    data->streams_list = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(data->streams_list), FALSE);

    controls = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(controls), play_button, FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(controls), pause_button, FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(controls), stop_button, FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(controls), data->slider, TRUE, TRUE, 2);

    main_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(main_hbox), video_window, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_hbox), data->streams_list, FALSE, FALSE, 2);

    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_box), main_hbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), controls, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(main_window), main_box);
    gtk_window_set_default_size(GTK_WINDOW(main_window), 640, 480);

    gtk_widget_show_all(main_window);
}

static gboolean refresh_ui(MyCustomData *data)
{
    gint64 current = -1;

    /* We do not want to update anything unless we are in the PAUSED or PLAYING states */
    if (data->state < GST_STATE_PAUSED)
        return TRUE;

    GSTWSeeker query = GSTWSeeker(data->playbin);

    /* If we didn't know it yet, query the stream duration */
    if (!GST_CLOCK_TIME_IS_VALID(data->duration))
    {
        if (!query.QueryDuration(&data->duration))
        {
            g_printerr("Could not query current duration.\n");
        }
        else
        {
            /* Set the range of the slider to the clip duration, in SECONDS */
            gtk_range_set_range(GTK_RANGE(data->slider), 0, (gdouble)data->duration / GST_SECOND);
        }
    }

    if (query.QueryPosition(&current))
    {
        /* Block the "value-changed" signal, so the slider_cb function is not called
     * (which would trigger a seek the user has not requested) */
        g_signal_handler_block(data->slider, data->slider_update_signal_id);
        /* Set the position of the slider to the current pipeline positoin, in SECONDS */
        gtk_range_set_value(GTK_RANGE(data->slider), (gdouble)current / GST_SECOND);
        /* Re-enable the signal */
        g_signal_handler_unblock(data->slider, data->slider_update_signal_id);
    }

    return TRUE;
}

/* Extract metadata from all the streams and write it to the text widget in the GUI */
static void analyze_streams(MyCustomData *data)
{
    gchar *total_str;
    GtkTextBuffer *text;

    /* Clean current contents of the widget */
    text = gtk_text_view_get_buffer(GTK_TEXT_VIEW(data->streams_list));
    gtk_text_buffer_set_text(text, "", -1);

    vector<VideoTags> videoTags = data->playbin->GetVideoTags();
    vector<AudioTags> audioTags = data->playbin->GetAudioTags();
    vector<SubtitleTags> subtitleTags = data->playbin->GetSubtitleTags();

    for (auto const &value : videoTags)
    {
        total_str = g_strdup_printf("video stream %d:\n", value.StreamIndex);
        gtk_text_buffer_insert_at_cursor(text, total_str, -1);
        g_free(total_str);

        total_str = g_strdup_printf("  codec: %s\n", !value.Codec.empty() ? value.Codec.c_str() : "unknown");
        gtk_text_buffer_insert_at_cursor(text, total_str, -1);
        g_free(total_str);
    }

    for (auto const &value : audioTags)
    {
        total_str = g_strdup_printf("\naudio stream %d:\n", value.StreamIndex);
        gtk_text_buffer_insert_at_cursor(text, total_str, -1);
        g_free(total_str);

        if (!value.Codec.empty())
        {
            total_str = g_strdup_printf("  codec: %s\n", value.Codec.c_str());
            gtk_text_buffer_insert_at_cursor(text, total_str, -1);
            g_free(total_str);
        }

        if (!value.Language.empty())
        {
            total_str = g_strdup_printf("  language: %s\n", value.Language.c_str());
            gtk_text_buffer_insert_at_cursor(text, total_str, -1);
            g_free(total_str);
        }

        if (value.Bitrate > 0)
        {
            total_str = g_strdup_printf("  bitrate: %d\n", value.Bitrate);
            gtk_text_buffer_insert_at_cursor(text, total_str, -1);
            g_free(total_str);
        }
    }

    for (auto const &value : subtitleTags)
    {
        total_str = g_strdup_printf("\nsubtitle stream %d:\n", value.StreamIndex);
        gtk_text_buffer_insert_at_cursor(text, total_str, -1);
        g_free(total_str);
        if (!value.Language.empty())
        {
            total_str = g_strdup_printf("  language: %s\n", value.Language.c_str());
            gtk_text_buffer_insert_at_cursor(text, total_str, -1);
            g_free(total_str);
        }
    }
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
    data.playbin = new GSTWPlayBin("playbin");
    GSTWMessageLogger *logger = new GSTWMessageLogger(data.playbin);

    data.playbin->CreateElement();

    /* Set the URI to play */
    data.playbin->SetUri("https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm");

    data.playbin->OnVideoTagsChanged(&data);
    data.playbin->OnAudioTagsChanged(&data);
    data.playbin->OnTextTagsChanged(&data);

    create_ui (&data);

    GSTWBus *bus = data.playbin->GetBus();

    //bus->AddMessageHandler(logger);
    bus->AddMessageHandler(&data);

    bus->BeginWatch();

    data.playbin->SetToPlayingState();

    /* Register a function that GLib will call every second */
    g_timeout_add_seconds(1, (GSourceFunc)refresh_ui, &data);
    //
    ///* Start the GTK main loop. We will not regain control until gtk_main_quit is called. */
    gtk_main();

    data.playbin->SetToNullState();

    delete logger;

    delete bus;

    delete data.playbin;

    return 0;
}