#include "gst/gst.h"
#include "StaticPad.h"
#include "RequestPad.h"
#include "DynamicPad.h"
#include "PadFilter.h"
#include "ElementFactory.h"
#include <string>
#include <vector>

using namespace std;

#ifndef GSTWELEMENT_H
#define GSTWELEMENT_H

class GSTWElement;

class GSTWSignalHandler
{
public:
    GSTWSignalHandler();
    ~GSTWSignalHandler();
    virtual void ConnectToSignal(GSTWElement* element) = 0;
};

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
    GSTWStaticPad *GetSinkStaticPad();
    GSTWRequestPad *GetSinkRequestPad(gint index);
    GSTWStaticPad *GetSrcStaticPad();
    GSTWRequestPad *GetSrcRequestPad(gint index);
    void SendApplicationMessage(string messageName);
    bool GetStaticPadTemplates(GSTWStaticPadTemplate** staticTemplate);
    void ConnectToSignal(GSTWSignalHandler* handler);
};

#endif
