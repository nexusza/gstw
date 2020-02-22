#include "gst/gst.h"
#include <string>
#include "Capabilities.h"

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
    string PadName;
    GstPad* _GstPad;
    bool GetCapabilities(GSTWCapabilities **capabilities);
    void LinkSourcePad(GstElement* _gstSourceElement, GstPad* _gstSourcePad);
};

#endif