#include "CustomBin.h"

GSTWCustomBin::GSTWCustomBin(string friendlyName) : GSTWBin(friendlyName, friendlyName)
{
}

GSTWCustomBin::~GSTWCustomBin()
{
}

void GSTWCustomBin::CreateElement()
{
    this->_GstElement = gst_bin_new(this->FriendlyName.c_str());
}

void GSTWCustomBin::AddSrcGhostPad()
{
    if(!gst_element_add_pad (this->_GstElement, gst_ghost_pad_new_no_target ("src", GST_PAD_SRC)))
    {
        g_printerr ("Failed to src add ghost pad in bin\n");
    }
}

void GSTWCustomBin::LinkSrcGhostPad(GSTWPad* pad)
{
    GSTWStaticPad* src = this->GetSrcStaticPad();
    
    if(gst_ghost_pad_set_target (GST_GHOST_PAD (src->_GstPad), pad->_GstPad))
    {
        g_printerr ("Failed to link src pad to bin ghost pad\n");
    }

    delete src;
}