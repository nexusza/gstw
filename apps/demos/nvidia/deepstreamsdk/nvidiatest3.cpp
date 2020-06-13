#include <iostream>
#include "All.h"
#include "format.h"
#include "gstnvdsmeta.h"
#include <regex> 

/*
This sample builds on top of the deepstream-test1 sample to demonstrate how to:

* Use multiple sources in the pipeline.
* Use a uridecodebin so that any type of input (e.g. RTSP/File), any GStreamer
  supported container format, and any codec can be used as input.
* Configure the stream-muxer to generate a batch of frames and infer on the
  batch for better resource utilization.
* Extract the stream metadata, which contains useful information about the
  frames in the batched buffer.

Refer to the deepstream-test1 sample documentation for an example of simple
single-stream inference, bounding-box overlay, and rendering.

This sample accepts one or more H.264/H.265 video streams as input. It creates
a source bin for each input and connects the bins to an instance of the
"nvstreammux" element, which forms the batch of frames. The batch of
frames is fed to "nvinfer" for batched inferencing. The batched buffer is
composited into a 2D tile array using "nvmultistreamtiler." The rest of the
pipeline is similar to the deepstream-test1 sample.

The "width" and "height" properties must be set on the stream-muxer to set the
output resolution. If the input frame resolution is different from
stream-muxer's "width" and "height", the input frame will be scaled to muxer's
output resolution.

The stream-muxer waits for a user-defined timeout before forming the batch. The
timeout is set using the "batched-push-timeout" property. If the complete batch
is formed before the timeout is reached, the batch is pushed to the downstream
element. If the timeout is reached before the complete batch can be formed
(which can happen in case of rtsp sources), the batch is formed from the
available input buffers and pushed. Ideally, the timeout of the stream-muxer
should be set based on the framerate of the fastest source. It can also be set
to -1 to make the stream-muxer wait infinitely.

The "nvmultistreamtiler" composite streams based on their stream-ids in
row-major order (starting from stream 0, left to right across the top row, then
across the next row, etc.).
*/

#define TILED_OUTPUT_WIDTH 1920
#define TILED_OUTPUT_HEIGHT 1080

#define MAX_DISPLAY_LEN 64

#define PGIE_CLASS_ID_VEHICLE 0
#define PGIE_CLASS_ID_PERSON 2

/* The muxer output resolution must be set if the input streams will be of
 * different resolution. The muxer will scale all the input frames to this
 * resolution. */
#define MUXER_OUTPUT_WIDTH 1920
#define MUXER_OUTPUT_HEIGHT 1080

/* Muxer batch formation timeout, for e.g. 40 millisec. Should ideally be set
 * based on the fastest source's framerate. */
#define MUXER_BATCH_TIMEOUT_USEC 4000000

#define GST_CAPS_FEATURES_NVMM "memory:NVMM"

///home/nanonexusza/Downloads/deepstream_sdk_v4.0.2_jetson/samples/streams/sample_1080p_h264.mp4

gint frame_number = 0;
gchar pgie_classes_str[4][32] = { "Vehicle", "TwoWheeler", "Person",
  "Roadsign"
};

class HandlePadProbe : public GSTWPadProbeHandler
{
    void OnHandlePadProbe(GstPad* pad, GstPadProbeInfo * info)
    {
    GstBuffer *buf = (GstBuffer *) info->data;
    guint num_rects = 0; 
    NvDsObjectMeta *obj_meta = NULL;
    guint vehicle_count = 0;
    guint person_count = 0;
    NvDsMetaList * l_frame = NULL;
    NvDsMetaList * l_obj = NULL;
    NvDsDisplayMeta *display_meta = NULL;

    NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta (buf);

    for (l_frame = batch_meta->frame_meta_list; l_frame != NULL;
      l_frame = l_frame->next) {
        NvDsFrameMeta *frame_meta = (NvDsFrameMeta *) (l_frame->data);
        int offset = 0;
        for (l_obj = frame_meta->obj_meta_list; l_obj != NULL;
                l_obj = l_obj->next) {
            obj_meta = (NvDsObjectMeta *) (l_obj->data);
            if (obj_meta->class_id == PGIE_CLASS_ID_VEHICLE) {
                vehicle_count++;
                num_rects++;
            }
            if (obj_meta->class_id == PGIE_CLASS_ID_PERSON) {
                person_count++;
                num_rects++;
            }
        }
        display_meta = nvds_acquire_display_meta_from_pool(batch_meta);
        NvOSD_TextParams *txt_params  = &display_meta->text_params[0];
        display_meta->num_labels = 1;
        //txt_params->display_text = g_malloc0 (MAX_DISPLAY_LEN);
        txt_params->display_text =new char[MAX_DISPLAY_LEN];
        offset = snprintf(txt_params->display_text, MAX_DISPLAY_LEN, "Person(s) = %d ", person_count);
        offset = snprintf(txt_params->display_text + offset , MAX_DISPLAY_LEN, "Vehicle(s) = %d ", vehicle_count);

        // Now set the offsets where the string should appear 
        txt_params->x_offset = 10;
        txt_params->y_offset = 12;
        //gchar pad_name_src[16] = "src";
        gchar serif[16] = "Serif";

        // Font , font-color and font-size 
        txt_params->font_params.font_name = serif;
        txt_params->font_params.font_size = 10;
        txt_params->font_params.font_color.red = 1.0;
        txt_params->font_params.font_color.green = 1.0;
        txt_params->font_params.font_color.blue = 1.0;
        txt_params->font_params.font_color.alpha = 1.0;

        // Text background color 
        txt_params->set_bg_clr = 1;
        txt_params->text_bg_clr.red = 0.0;
        txt_params->text_bg_clr.green = 0.0;
        txt_params->text_bg_clr.blue = 0.0;
        txt_params->text_bg_clr.alpha = 1.0;

        nvds_add_display_meta_to_frame(frame_meta, display_meta);
    }
    g_print ("Frame Number = %d Number of objects = %d "
            "Vehicle Count = %d Person Count = %d\n",
            frame_number, num_rects, vehicle_count, person_count);
    frame_number++;
    }
};

class GSTWLinkGhostPadSignalHandler : public GSTWPadAddedSignalHandler
{
protected:
    GSTWCustomBin* bin;
    void OnHandlePadAddedSignal(GSTWElement *element, GSTWDynamicPad* pad)
    {
      g_print("Linking ghost pad.\n");
      bin->LinkSrcGhostPad(pad);
    }
public:
    GSTWLinkGhostPadSignalHandler(GSTWCustomBin* bin)
    {
        this->bin = bin;

        GSTWVideoPadFilter* videoFilter = new GSTWVideoPadFilter();

        videoFilter->AddFilter(new GSTWPadFeatureFilter(GST_CAPS_FEATURES_NVMM));

        this->UsePadFilter(videoFilter);
    }
};

class SetupBufApiHandler : public GSTWChildAddedSignalHandler
{
public:
    SetupBufApiHandler()
    {
      this->AddRegexNameFilter("(decodebin)(.*)");
      this->AddRegexNameFilter("(nvv4l2decoder)(.*)");
    }
    void OnHandleChildAddedSignal(GSTWElement* element, string name)
    {
      GSTWNvv4l2Decoder *decoder = new GSTWNvv4l2Decoder(element->_GstElement);

      g_print("Setting buf api version.\n");

      decoder->SetBufApiVersion(true);

      delete decoder;
    }
};

int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    if(!regex_match("myvalue0", regex("(myvalue)(.*)")))
    {
      return false;
    }

    GSTWCustomPipeline *pipeline = new GSTWCustomPipeline("mypipeline");
    GSTWMessageLogger *logger = new GSTWMessageLogger(pipeline);
    GSTWNvStreamMux *mux = new GSTWNvStreamMux("mux");
    GSTWNvInfer *pgie = new GSTWNvInfer("infer");
    GSTWNvMultistreamTiler *tiler = new GSTWNvMultistreamTiler("tiler");
    GSTWNvDsosd *osd = new GSTWNvDsosd("osd");
    GSTWNvVideoConvert *convert = new GSTWNvVideoConvert("convert");
    GSTWNvVideoConvert *convertosd = new GSTWNvVideoConvert("convertosd");
    GSTWCapsFilter *caps = new GSTWCapsFilter("caps");
    GSTWNvv4l2H264Enc *encode = new GSTWNvv4l2H264Enc("encode");
    GSTWRtph264Pay *payload = new GSTWRtph264Pay("rtppayload");
    GSTWUdpSink *udp = new GSTWUdpSink("udpsink");

    pipeline->CreateElement();
    pipeline->AddElement(mux);
   
    //int num_sources = argc - 1;
    int num_sources = 2;
    for (int i = 0; i < num_sources; i++) {

        GSTWCustomBin *bin = new GSTWCustomBin(fmt::format("custombin-{0}.", i));
        GSTWUriDecodeBin *decodebin = new GSTWUriDecodeBin("decodebin");

        pipeline->AddElement(bin);

        bin->AddElement(decodebin);

        bin->AddSrcGhostPad();

        //decodebin->SetUri(argv[i + 1]);
        decodebin->SetUri("file:///home/nanonexusza/Downloads/deepstream_sdk_v4.0.2_jetson/samples/streams/sample_1080p_h264.mp4");

        GSTWLinkGhostPadSignalHandler* ghostPadHandler = new GSTWLinkGhostPadSignalHandler(bin);

        decodebin->ConnectToSignal(ghostPadHandler);

        SetupBufApiHandler* bufApiHandler = new SetupBufApiHandler();
        
        decodebin->ConnectToSignal(bufApiHandler);

        GSTWStaticPad* decodeSrc = bin->GetSrcStaticPad();
        GSTWRequestPad *requestPad = mux->GetSinkRequestPad(i);

        decodeSrc->LinkPad(requestPad);
    }


    pipeline->AddElement(pgie);
    pipeline->AddElement(tiler);
    pipeline->AddElement(convert);
    pipeline->AddElement(osd);
    pipeline->AddElement(convertosd);
    pipeline->AddElement(caps);
    pipeline->AddElement(encode);
    pipeline->AddElement(payload);
    pipeline->AddElement(udp);

    pgie->SetConfigFilePath("/home/nanonexusza/Development/git/gstw/apps/demos/nvidia/deepstreamsdk/config/nvidiatest1.txt");

    mux
    ->AutoLinkElement(pgie)
    ->AutoLinkElement(tiler)
    ->AutoLinkElement(convert)
    ->AutoLinkElement(osd)
    ->AutoLinkElement(convertosd)
    ->AutoLinkElement(caps)
    ->AutoLinkElement(encode)
    ->AutoLinkElement(payload)
    ->AutoLinkElement(udp);   

    caps->SetCapsFromString("video/x-raw(memory:NVMM), width=(int)1920, height=(int)1080, format=(string)NV12, framerate=(fraction)30/1");

    mux->SetWidth(MUXER_OUTPUT_WIDTH);
    mux->SetHeight(MUXER_OUTPUT_HEIGHT);
    mux->SetBatchSize(1);
    mux->SetBatchedPushTimeout(MUXER_OUTPUT_HEIGHT);

    tiler->SetRowsAndColumns(num_sources);
    tiler->SetHeight(TILED_OUTPUT_HEIGHT);
    tiler->SetWidth(TILED_OUTPUT_WIDTH);

    GSTWStaticPad* osdSinkPad = osd->GetSinkStaticPad();
    HandlePadProbe* probe = new HandlePadProbe();

    osdSinkPad->Probe(probe);
    
    //source->SetLocation("/home/nanonexusza/Downloads/deepstream_sdk_v4.0.2_jetson/samples/streams/sample_1080p_h264.mp4");

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