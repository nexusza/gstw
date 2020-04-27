#include <iostream>
#include "All.h"

int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    GSTWCustomPipeline *pipeline = new GSTWCustomPipeline("mypipeline");
    GSTWMessageLogger *logger = new GSTWMessageLogger(pipeline);
    GSTWUriDecodeBin *source = new GSTWUriDecodeBin("uridecode");
    GSTWVideoConvert *convert = new GSTWVideoConvert("videoconvert");
    GSTWX264Enc *encode = new GSTWX264Enc("encode");
    GSTWRtph264Pay *payload = new GSTWRtph264Pay("rtppayload");
    GSTWUdpSink *udp = new GSTWUdpSink("udpsink");
    GSTWPadLinkEventHandler* padAdded = new GSTWPadLinkEventHandler(convert);

    pipeline->CreateElement();

    pipeline->AddElement(source);

    pipeline->AddElement(convert);
    pipeline->AddElement(encode);
    pipeline->AddElement(payload);
    pipeline->AddElement(udp);//

    convert->AutoLinkElement(encode);
    encode->AutoLinkElement(payload);
    payload->AutoLinkElement(udp);

    //http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4
    source->SetUri("file:///home/nexusza/Downloads/BigBuckBunny.mp4");

    padAdded->ConnectToPadAddedSignalVideo(source);

    udp->SetPort(1234);

    pipeline->SetToPlayingState();

    GSTWBus *bus = pipeline->GetBus();

    bus->AddMessageHandler(logger);

    bus->BeginWait();

    delete logger;
    delete bus;

    pipeline->SetToNullState();

    delete pipeline;

    return 0;
}