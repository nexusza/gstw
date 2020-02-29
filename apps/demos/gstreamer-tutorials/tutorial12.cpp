#include "All.h"
#include <string.h>

class CustomData : public GSTWBusMessageHandler
{
public:
    GSTWPlayBin *playbin;
    GMainLoop *loop;
    bool isLive = false;

protected:
    void OnHandleError(GstBus *_gstBus, GSTWMessage *message)
    {
        this->playbin->SetToReadyState();
        g_main_loop_quit(this->loop);
    }

    void OnHandleEOS(GstBus *_gstBus, GSTWMessage *message)
    {
        this->playbin->SetToReadyState();
        g_main_loop_quit(this->loop);
    }

    void OnHandleBuffering(GstBus *_gstBus, GSTWMessage *message)
    {
        if (isLive)
        {
            return;
        }

        gint percent = message->ParseBufferingPercentage();

        g_print("Buffering (%3d%%)\r", percent);
        
        /* Wait until buffering is complete before start/resume playing */
        if (percent < 100)
            this->playbin->SetToPausedState();
        else
            this->playbin->SetToPlayingState();
    }

    void OnHandleClockLost(GstBus *_gstBus, GSTWMessage *message)
    {
        this->playbin->ResetClock();
    }
};

int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    CustomData data;

    GSTWPlayBin *pipeline = new GSTWPlayBin("playbin");

    data.loop = g_main_loop_new(NULL, FALSE);
    
    data.playbin = pipeline;

    pipeline->CreateElement();

    pipeline->SetUri("https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm");

    GSTWBus *bus = pipeline->GetBus();

    bus->AddMessageHandler(&data);

    bus->BeginWatch();

    GstStateChangeReturn ret = pipeline->SetToPlayingState();

    if (ret == GST_STATE_CHANGE_NO_PREROLL)
    {
        data.isLive = TRUE;
    }

    g_main_loop_run(data.loop);

    /* Free resources */
    g_main_loop_unref(data.loop);

    delete bus;
    delete pipeline;

    return 0;
}