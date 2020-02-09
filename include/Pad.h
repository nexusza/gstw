#include "gst/gst.h"
#include <string>

using std::string;

#ifndef GSTWPAD_H
#define GSTWPAD_H

class GSTWPad
{
private:
    /* data */
public:
    GSTWPad(GstElement* _gstElement, string padName);
    ~GSTWPad();
    GstPad* _GstPad;
    void LinkSourcePad(GstElement* _gstSourceElement, GstPad* _gstSourcePad);
};

#endif