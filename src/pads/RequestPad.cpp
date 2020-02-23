#include "RequestPad.h"

GSTWRequestPad::GSTWRequestPad(GstElement* _gstElement, string padName) : GSTWPad(padName)
{
    this->_GstPad = gst_element_get_request_pad(_gstElement, PadName.c_str());
    this->_gstElement = _gstElement;
}

GSTWRequestPad::~GSTWRequestPad()
{
    gst_element_release_request_pad (this->_gstElement, this->_GstPad);
    this->_gstElement = nullptr;
}