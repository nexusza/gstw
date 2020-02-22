#include "gst/gst.h"
#include "MessageLogger.h"

GSTWMessageLogger::GSTWMessageLogger(/* args */)
{
}

GSTWMessageLogger::GSTWMessageLogger(GSTWElement *element)
{
    this->Element = element;
}

GSTWMessageLogger::~GSTWMessageLogger()
{
}

void GSTWMessageLogger::OnHandleStateChanged(GstBus *_gstBus, GSTWMessage *message)
{
    if (this->Element == nullptr || message->IsForElement(this->Element))
    {
        g_print("Pipeline state changed from %s to %s:\n",
                gst_element_state_get_name(message->OldState), gst_element_state_get_name(message->NewState));
    }
}

void GSTWMessageLogger::OnHandleTimeout(GstBus *_gstBus, GSTWMessage *message)
{
}

void GSTWMessageLogger::OnHandleEOS(GstBus *_gstBus, GSTWMessage *message)
{
    g_print("End-Of-Stream reached.\n");
}

void GSTWMessageLogger::OnHandleError(GstBus *_gstBus, GSTWMessage *message)
{
    GError *err;
    gchar *debug_info;
    gst_message_parse_error(message->_GstMessage, &err, &debug_info);
    g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(message->_GstMessage->src), err->message);
    g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
    g_clear_error(&err);
    g_free(debug_info);
}