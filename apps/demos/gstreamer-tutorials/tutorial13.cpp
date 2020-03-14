#include <string.h>
#include <stdio.h>
#include "All.h"

class CustomData
{
public:
    GSTWPlayBin *pipeline;
    GSTWElement *video_sink = nullptr;
    GMainLoop *loop;

    gboolean playing; /* Playing or Paused */
    gdouble rate;     /* Current playback rate (can be negative) */
};

/* Send seek event to change rate */
static void send_seek_event(CustomData *data)
{
    if (data->video_sink == NULL)
    {
        /* If we have not done so, obtain the sink through which we will send the seek events */
        data->video_sink = data->pipeline->GetVideoSink();
    }

    GSTWSeeker seeker = GSTWSeeker(data->video_sink);

    /* Create the seek event */
    if (data->rate > 0)
    {
        seeker.SeekForward(data->rate);
    }
    else
    {
        seeker.SeekBackward(data->rate);
    }

    g_print("Current rate: %g\n", data->rate);
}

static gboolean handle_keyboard(GIOChannel *source, GIOCondition cond, CustomData *data)
{
    gchar *str = NULL;

    if (g_io_channel_read_line(source, &str, NULL, NULL,
                               NULL) != G_IO_STATUS_NORMAL)
    {
        return TRUE;
    }

    switch (g_ascii_tolower(str[0]))
    {
    case 'p':
        data->playing = !data->playing;
        data->pipeline->SetToState(data->playing ? GST_STATE_PLAYING : GST_STATE_PAUSED);
        g_print("Setting state to %s\n", data->playing ? "PLAYING" : "PAUSE");
        break;
    case 's':
        if (g_ascii_isupper(str[0]))
        {
            data->rate *= 2.0;
        }
        else
        {
            data->rate /= 2.0;
        }
        send_seek_event(data);
        break;
    case 'd':
        data->rate *= -1.0;
        send_seek_event(data);
        break;
    case 'n':
    {
        if (data->video_sink == nullptr)
        {
            /* If we have not done so, obtain the sink through which we will send the step events */
            data->video_sink = data->pipeline->GetVideoSink();
        }

        GSTWSeeker seeker = GSTWSeeker(data->video_sink);

        seeker.StepFrame(ABS(data->rate));

        g_print("Stepping one frame\n");

        break;
    }
    case 'q':
        g_main_loop_quit(data->loop);
        break;
    default:
        break;
    }

    g_free(str);

    return TRUE;
}

int main(int argc, char *argv[])
{
    CustomData data;
    GIOChannel *io_stdin;

    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    /* Print usage map */
    g_print("USAGE: Choose one of the following options, then press enter:\n"
            " 'P' to toggle between PAUSE and PLAY\n"
            " 'S' to increase playback speed, 's' to decrease playback speed\n"
            " 'D' to toggle playback direction\n"
            " 'N' to move to next frame (in the current direction, better in PAUSE)\n"
            " 'Q' to quit\n");

    /* Build the pipeline */

    GSTWPlayBin *pipeline = new GSTWPlayBin("playbin");

    pipeline->CreateElement();

    //pipeline->SetUri("https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm");
    pipeline->SetUri("file:///home/nexusza/Downloads/sintel_trailer-480p.webm");

    data.pipeline = pipeline;

    /* Add a keyboard watch so we get notified of keystrokes */
#ifdef G_OS_WIN32
    io_stdin = g_io_channel_wicln32_new_fd(fileno(stdin));
#else
    io_stdin = g_io_channel_unix_new(fileno(stdin));
#endif

    g_io_add_watch(io_stdin, G_IO_IN, (GIOFunc)handle_keyboard, &data);

    /* Start playing */
    pipeline->SetToPlayingState();

    data.playing = TRUE;

    data.rate = 1.0;

    /* Create a GLib Main Loop and set it to run */
    data.loop = g_main_loop_new(NULL, FALSE);

    g_main_loop_run(data.loop);

    /* Free resources */
    g_main_loop_unref(data.loop);

    g_io_channel_unref(io_stdin);

    pipeline->SetToNullState();

    if (data.video_sink != NULL)
        gst_object_unref(data.video_sink);

    delete pipeline;

    return 0;
}