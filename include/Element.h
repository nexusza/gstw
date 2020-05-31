#include "gst/gst.h"
#include "StaticPad.h"
#include "DynamicPad.h"
#include "PadFilter.h"
#include "ElementFactory.h"
#include <string>
#include <vector>

using namespace std;

#ifndef GSTWELEMENT_H
#define GSTWELEMENT_H

class GSTWElement;

class GSTWPadAddedSignalHandler
{
private:
    GSTWPadFilter* padFilter;
public:
    GSTWPadAddedSignalHandler();
    ~GSTWPadAddedSignalHandler();
    void UsePadFilter(GSTWPadFilter* padFilter);
    void HandlePadAddedSignal(GstElement *element, GstPad* pad);
protected:
    virtual void OnHandlePadAddedSignal(GSTWElement *element, GSTWDynamicPad* pad) = 0;
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
    GSTWStaticPad *GetSinkPad();
    GSTWStaticPad *GetSrcPad();
    void SendApplicationMessage(string messageName);
    bool GetStaticPadTemplates(GSTWStaticPadTemplate** staticTemplate);
    void ConnectToPadAddedSignal(GSTWPadAddedSignalHandler* handler);
};

static void gstw_pad_added_event(GstElement *src, GstPad *new_pad, GSTWPadAddedSignalHandler *handler);

#endif
