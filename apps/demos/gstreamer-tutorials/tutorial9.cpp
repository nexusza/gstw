#include "All.h"

/* Structure to contain all our information, so we can pass it around */
class CustomData : public GSTWDiscoverer
{
public:
    CustomData(string uri)
        : GSTWDiscoverer(uri)
    {
    }

    ~CustomData()
    {
    }

    GMainLoop *loop;

    void OnDiscovererFinshed()
    {
        g_print("Finished discovering\n");

        g_main_loop_quit(loop);
    }
};

int main(int argc, char **argv)
{

    string uri = "https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm";

    CustomData data = CustomData(uri);

    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    /* Instantiate the Discoverer */

    if (!data.CreateDiscoverer(5))
    {
        return -1;
    }

    if (!data.StartDiscoverer())
    {
        return -1;
    }

    /* Create a GLib Main Loop and set it to run, so we can wait for the signals */
    data.loop = g_main_loop_new(NULL, FALSE);

    g_main_loop_run(data.loop);

    data.StopDiscoverer();

    g_main_loop_unref(data.loop);

    return 0;
}