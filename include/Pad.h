#include "gst/gst.h"
#include <string>
#include "Capabilities.h"

using namespace std;

#ifndef GSTWPAD_H
#define GSTWPAD_H

class GSTWPad
{
private:
    string padName;
    string padType;
public:
    GSTWPad();
    ~GSTWPad();
    GstPad* _GstPad;
    bool GetCapabilities(GSTWCapabilities **capabilities);
    void LinkSourcePad(GstElement* _gstSourceElement, GstPad* _gstSourcePad, string targetElementName, string padType);
    void LinkPad(GSTWPad *pad);
    bool IsLinked();
    string GetPadName();
    string GetPadType();
};

#endif