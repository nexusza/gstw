#include "gst/gst.h"
#include <string>
#include "Capabilities.h"

using namespace std;

#ifndef GSTWPAD_H
#define GSTWPAD_H

class GSTWPad
{
private:
    /* data */
public:
    GSTWPad(string padName);
    ~GSTWPad();
    string PadName;
    GstPad* _GstPad;
    bool GetCapabilities(GSTWCapabilities **capabilities);
    void LinkSourcePad(GstElement* _gstSourceElement, GstPad* _gstSourcePad);
    void LinkPad(GSTWPad *pad);
};

#endif