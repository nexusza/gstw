#include "gst/gst.h"
#include "StaticPad.h"
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
    GSTWElement(GstElement *_gstElement);
    ~GSTWElement();

    string FriendlyName;
    string GetName();
    GstElement *_GstElement;
    GSTWElementFactory *Factory;
    virtual void CreateElement();
    GSTWElement *AutoLinkElement(GSTWElement *element);
    GSTWStaticPad *GetSinkPad();
    GSTWStaticPad *GetSrcPad();
    void SendApplicationMessage(string messageName);
    bool GetStaticPadTemplates(GSTWStaticPadTemplate** staticTemplate);
};

#endif
