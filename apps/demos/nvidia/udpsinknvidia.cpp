#include <iostream>
#include "All.h"

int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    GSTWCustomPipeline *pipeline = new GSTWCustomPipeline("mypipeline");
    GSTWMessageLogger *logger = new GSTWMessageLogger(pipeline);
    GSTWSoupHttpSrc *source = new GSTWSoupHttpSrc("httpsource");
    GSTWDecodeBin *decodebin = new GSTWDecodeBin("decodebin");
    GSTWQtDemux *demux = new GSTWQtDemux("demux");
    GSTWQueue *queue = new GSTWQueue("queue");
    GSTWH264Parse *parse = new GSTWH264Parse("parse");
    GSTWNvv4l2Decoder *decode = new GSTWNvv4l2Decoder("decode");
    GSTWCapsFilter *caps = new GSTWCapsFilter("caps");
    GSTWNvv4l2H264Enc *encode = new GSTWNvv4l2H264Enc("encode");
    GSTWRtph264Pay *payload = new GSTWRtph264Pay("rtppayload");
    GSTWUdpSink *udp = new GSTWUdpSink("udpsink");
    GSTWAutoVideoSink *convert = new GSTWAutoVideoSink("videoconvert");

    GSTWPadLinkEventHandler* padAdded = new GSTWPadLinkEventHandler(queue, "whater");

    pipeline->CreateElement();

    pipeline->AddElement(source);
    pipeline->AddElement(demux);
    pipeline->AddElement(queue);
    //pipeline->AddElement(decodebin);
    //pipeline->AddElement(convert);
    //pipeline->AddElement(queue);
    pipeline->AddElement(parse);
    pipeline->AddElement(decode);
    pipeline->AddElement(caps);
    pipeline->AddElement(encode);
    pipeline->AddElement(payload);
    pipeline->AddElement(udp);
   
    
    source->AutoLinkElement(demux);
    //queue->AutoLinkElement(decodebin);
    //decodebin->AutoLinkElement(convert);
    //demux->AutoLinkElement(queue);
    queue->AutoLinkElement(parse);
    parse->AutoLinkElement(decode);
    decode->AutoLinkElement(caps);
    caps->AutoLinkElement(encode);
    encode->AutoLinkElement(payload);
    payload->AutoLinkElement(udp);

    padAdded->ConnectToPadAddedSignalVideo(demux);

    //http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4
    source->SetLocation("http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4");

    //caps->SetCapsFromString("video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, format=(string)NV12, framerate=(fraction)24/1");

    udp->SetHost("192.168.1.50");

    udp->SetPort(5000);

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