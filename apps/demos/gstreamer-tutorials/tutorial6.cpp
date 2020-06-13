#include "All.h"
#include <vector>

using namespace std;

static gboolean print_field(GQuark field, const GValue *value, gpointer pfx);
static void print_caps(GSTWCapabilities *caps, string prefix);
static void print_pad_capabilities(GSTWPad *pad);

class PrintPads : public GSTWBusMessageHandler
{
private:
    GSTWElement *element;

public:
    PrintPads(GSTWElement *element)
    {
        this->element = element;
    };

    void OnHandleStateChanged(GstBus *_gstBus, GSTWMessage *message)
    {
        if (message->IsForElement(this->element))
        {
            GSTWStaticPad *sinkPad = this->element->GetSinkStaticPad();

            print_pad_capabilities(sinkPad);

            delete sinkPad;
        }
    }

    static void PrintStaticPadCaps(GSTWElement *element)
    {   
        g_print("Pad Templates for %s:\n", element->Factory->GetLongName().c_str());

        GSTWStaticPadTemplate *staticPadTemplate = nullptr;

        if (!element->GetStaticPadTemplates(&staticPadTemplate))
        {
            g_print("  none\n");
            return;
        }

        do
        {
            if (staticPadTemplate->_GstStaticPadTemplate->direction == GST_PAD_SRC)
                g_print("  SRC template: '%s'\n", staticPadTemplate->_GstStaticPadTemplate->name_template);
            else if (staticPadTemplate->_GstStaticPadTemplate->direction == GST_PAD_SINK)
                g_print("  SINK template: '%s'\n", staticPadTemplate->_GstStaticPadTemplate->name_template);
            else
                g_print("  UNKNOWN!!! template: '%s'\n", staticPadTemplate->_GstStaticPadTemplate->name_template);

            if (staticPadTemplate->_GstStaticPadTemplate->presence == GST_PAD_ALWAYS)
                g_print("    Availability: Always\n");
            else if (staticPadTemplate->_GstStaticPadTemplate->presence == GST_PAD_SOMETIMES)
                g_print("    Availability: Sometimes\n");
            else if (staticPadTemplate->_GstStaticPadTemplate->presence == GST_PAD_REQUEST)
                g_print("    Availability: On request\n");
            else
                g_print("    Availability: UNKNOWN!!!\n");

            GSTWCapabilities *caps;

            if (staticPadTemplate->GetCapabilities(&caps))
            {
                g_print ("    Capabilities:\n");
    
                print_caps(caps, "      ");

                delete caps;
            }
        } while (staticPadTemplate->GetNextTemplate(&staticPadTemplate));
    }
};

/* Functions below print the Capabilities in a human-friendly format */
static gboolean print_field(GQuark field, const GValue *value, gpointer pfx)
{
    gchar *str = gst_value_serialize(value);

    g_print("%s  %15s: %s\n", (gchar *)pfx, g_quark_to_string(field), str);
    g_free(str);
    return TRUE;
}

static void print_caps(GSTWCapabilities *caps, string prefix)
{
    const gchar *pfx = prefix.c_str();

    if (caps->IsAny())
    {
        g_print("%sANY\n", pfx);
        return;
    }
    else if (caps->IsEmpty())
    {
        g_print("%sEMPTY\n", pfx);
        return;
    }

    vector<GstStructure *> gstStructures = caps->GetGstStructures();

    for (auto &structure : gstStructures)
    {
        g_print("%s%s\n", pfx, gst_structure_get_name(structure));

        gst_structure_foreach(structure, print_field, (gpointer)pfx);
    }
}

/* Shows the CURRENT capabilities of the requested pad in the given element */
static void print_pad_capabilities(GSTWPad *pad)
{
    GSTWCapabilities *caps;

    if (pad->GetCapabilities(&caps))
    {
        g_print("Caps for the %s pad:\n", pad->GetPadName().c_str());

        print_caps(caps, "      ");

        delete caps;
    }
}

int main(int argc, char *argv[])
{
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    GSTWCustomPipeline *pipeline = new GSTWCustomPipeline("testpipeline");
    GSTWAudioTestSrc *audiotest = new GSTWAudioTestSrc("audiotestsrc");
    GSTWAutoAudioSink *audiosink = new GSTWAutoAudioSink("audiosink");
    GSTWMessageLogger *logger = new GSTWMessageLogger(pipeline);
    PrintPads *printPads = new PrintPads(audiosink);

    pipeline->CreateElement();
    audiotest->CreateElement();
    audiosink->CreateElement();

    PrintPads::PrintStaticPadCaps(audiotest);
    PrintPads::PrintStaticPadCaps(audiosink);

    pipeline->AddElement(audiotest);
    pipeline->AddElement(audiosink);

    audiotest->AutoLinkElement(audiosink);

    pipeline->SetToPlayingState();

    GSTWBus *bus = pipeline->GetBus();

    bus->AddMessageHandler(logger);
    bus->AddMessageHandler(printPads);

    bus->BeginWait();

    pipeline->SetToNullState();

    delete logger;
    delete printPads;
    delete audiosink;
    delete audiotest;
    delete pipeline;

    return 0;
}