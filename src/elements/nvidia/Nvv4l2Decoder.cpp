#include "Nvv4l2Decoder.h"

GSTWNvv4l2Decoder::GSTWNvv4l2Decoder(string friendlyName) : GSTWElement("nvv4l2decoder", friendlyName)
{
}

GSTWNvv4l2Decoder::GSTWNvv4l2Decoder(GstElement* _gstElement) : GSTWElement(_gstElement)
{
}

GSTWNvv4l2Decoder::~GSTWNvv4l2Decoder()
{
}

void GSTWNvv4l2Decoder::SetBufApiVersion(gboolean value)
{
    g_object_set (this->_GstElement, "bufapi-version", value, NULL);
}