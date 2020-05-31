#include "RequestPad.h"

GSTWRequestPad::GSTWRequestPad(GstElement* _gstElement, string padName) : GSTWPad()
{
    this->_GstPad = gst_element_get_request_pad(_gstElement, padName.c_str());
    this->_gstElement = _gstElement;
}

GSTWRequestPad::~GSTWRequestPad()
{
    gst_element_release_request_pad (this->_gstElement, this->_GstPad);

    gst_object_unref(this->_GstPad);

    this->_GstPad = nullptr;
    this->_gstElement = nullptr;
}