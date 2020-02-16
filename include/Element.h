#include "gst/gst.h"
#include "SinkPad.h"
#include <string>

using namespace std;

#ifndef GSTWELEMENT_H
#define GSTWELEMENT_H

class GSTWElement
{
    public:
        GSTWElement(string elementName, string friendlyName);
        ~GSTWElement();
        
        string ElementName;
        string FriendlyName;
        GstElement* _GstElement;

        virtual void CreateElement();
        void Link(GSTWElement *element);
        GSTWSinkPad* GetSinkPad();
        void SendApplicationMessage(string messageName);
};

#endif

