#include "SinkPad.h"

GSTWSinkPad::GSTWSinkPad(GstElement* _gstElement) : GSTWPad(_gstElement, "sink")
{
}

GSTWSinkPad::~GSTWSinkPad()
{
}