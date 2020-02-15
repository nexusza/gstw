#include <iostream>
#include "All.h"

class MySeeker : public GSTWBusMessageHandler
{
private:
    /* data */
public:
    MySeeker(GSTWElement *element);
    ~MySeeker();

    void OnHandleDurationChange(GstBus *_gstBus, GSTWMessage *message);
    void OnHandleStateChanged(GstBus *_gstBus, GSTWMessage *message);
    void OnHandleTimeout();

    GSTWElement *Element;
    gboolean SeekDone;
    gboolean CanSeek;
    gint64 Duration;
    gint64 Start;
    gint64 End;
};

MySeeker::MySeeker(GSTWElement *element) : GSTWBusMessageHandler()
{
    this->Element = element;
    this->CanSeek = false;
    this->SeekDone = false;
}

MySeeker::~MySeeker()
{
}

void MySeeker::OnHandleDurationChange(GstBus *_gstBus, GSTWMessage *message)
{
    this->CanSeek = false;
}

void MySeeker::OnHandleStateChanged(GstBus *_gstBus, GSTWMessage *message)
{
    if (message->IsForElement(this->Element->_GstElement))
    {
        if (message->IsPlaying())
        {
            GSTWSeekQuery query;
            this->CanSeek = query.QuerySeekRange(this->Element->_GstElement, &this->Start, &this->End, &this->Duration);
        }
        else
        {
            this->CanSeek = false;
        }
    }
}

void MySeeker::OnHandleTimeout()
{
    if (!this->CanSeek)
    {
        return;
    }

    GSTWSeekQuery query;

    gint64 current = query.QueryCurrent(this->Element->_GstElement);

    /* Print current position and total duration */
    g_print("Position %" GST_TIME_FORMAT " / %" GST_TIME_FORMAT "\r",
            GST_TIME_ARGS(current), GST_TIME_ARGS(this->Duration));

    /* If seeking is enabled, we have not done it yet, and the time is right, seek */
    if (this->CanSeek && !this->SeekDone && current > 10 * GST_SECOND)
    {
        GSTWSeeker seeker = GSTWSeeker(this->Element);

        g_print("\nReached 10s, performing seek...\n");

        seeker.SeekSimple(30);
        this->SeekDone = true;
    }
}

int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    GSTWPlayBin *pipeline = new GSTWPlayBin("source");

    pipeline->CreateElement();

    GSTWMessageLogger *messageLogger = new GSTWMessageLogger(pipeline);

    MySeeker *seeker = new MySeeker(pipeline);

    GSTWBus *bus = pipeline->GetBus();

    bus->AddMessageHandler(messageLogger);

    bus->AddMessageHandler(seeker);

    pipeline->Uri()->Set("https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm");

    pipeline->Play();

    bus->BeginWait(100);

    delete bus;
    
    pipeline->Stop();

    delete messageLogger;
    delete seeker;
    delete pipeline;

    return 0;
}