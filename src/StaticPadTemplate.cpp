#include "gst/gst.h"
#include "StaticPadTemplate.h"

GSTWStaticPadTemplate::GSTWStaticPadTemplate(const GList *_list)
{
    this->_glist = _list;
    this->_GstStaticPadTemplate = (GstStaticPadTemplate *)_list->data;
}

GSTWStaticPadTemplate::~GSTWStaticPadTemplate()
{
    this->_glist = nullptr;
    this->_GstStaticPadTemplate = nullptr;
}

bool GSTWStaticPadTemplate::GetCapabilities(GSTWCapabilities **capabilities)
{
    if (this->_GstStaticPadTemplate->static_caps.string)
    {
        *capabilities = new GSTWCapabilities(gst_static_caps_get(&this->_GstStaticPadTemplate->static_caps));

        return true;
    }

    return false;
}

bool GSTWStaticPadTemplate::GetNextTemplate(GSTWStaticPadTemplate **staticTemplate)
{
    GList *next = g_list_next(this->_glist);

    if (next)
    {
        GSTWStaticPadTemplate *nextTemplate = new GSTWStaticPadTemplate(next);

        staticTemplate = &nextTemplate;
        return true;
    }

    return false;
}

bool GSTWStaticPadTemplate::GetStaticPadTemplates(GstElementFactory *_gstFactory, GSTWStaticPadTemplate **staticTemplate)
{
    vector<GSTWStaticPadTemplate *> list;

    const GList *pads;

    if (!gst_element_factory_get_num_pad_templates(_gstFactory))
    {
        return false;
    }

    pads = gst_element_factory_get_static_pad_templates(_gstFactory);

    if (pads)
    {
        *staticTemplate = new GSTWStaticPadTemplate(pads);
        return true;
    }

    return false;
}