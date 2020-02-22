#include "gst/gst.h"
#include "SinkPad.h"
#include "ElementFactory.h"
#include <string>
#include <vector>

using namespace std;

#ifndef GSTWELEMENT_H
#define GSTWELEMENT_H

class GSTWElement
{
public:
    GSTWElement(string elementName, string friendlyName);
    ~GSTWElement();

    string FriendlyName;
    GstElement *_GstElement;
    GSTWElementFactory *Factory;
    virtual void CreateElement();
    void Link(GSTWElement *element);
    GSTWSinkPad *GetSinkPad();
    void SendApplicationMessage(string messageName);
    bool GetStaticPadTemplates(GSTWStaticPadTemplate** staticTemplate);
};

#endif
