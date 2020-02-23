#include "StaticPad.h"

GSTWStaticPad::GSTWStaticPad(GstElement* _gstElement, string padName) : GSTWPad(padName)
{
    this->_GstPad = gst_element_get_static_pad(_gstElement, PadName.c_str());
}

GSTWStaticPad::~GSTWStaticPad()
{
}