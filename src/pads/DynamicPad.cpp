#include "DynamicPad.h"

GSTWDynamicPad::GSTWDynamicPad(GstPad* _gstPad) : GSTWPad()
{
    this->_GstPad = _gstPad;
}

GSTWDynamicPad::~GSTWDynamicPad()
{
    this->_GstPad = nullptr;
}