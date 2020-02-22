#include "gst/gst.h"
#include "Capabilities.h"

GSTWCapabilities::GSTWCapabilities(GstCaps *gstCaps)
{
    this->_GstCaps = gstCaps;
}

GSTWCapabilities::~GSTWCapabilities()
{
    gst_caps_unref(this->_GstCaps);
    this->_GstCaps = nullptr;
}

gboolean GSTWCapabilities::IsAny()
{
    return gst_caps_is_any(this->_GstCaps);
}

gboolean GSTWCapabilities::IsEmpty()
{
    return gst_caps_is_empty(this->_GstCaps);
}

vector<GstStructure *> GSTWCapabilities::GetGstStructures()
{
    vector<GstStructure *> list;

    for (guint i = 0; i < gst_caps_get_size(this->_GstCaps); i++)
    {
        list.push_back(gst_caps_get_structure(this->_GstCaps, i));
    }

    return list;
}