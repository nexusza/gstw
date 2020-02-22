#include "gst/gst.h"
#include "StaticPadTemplate.h"
#include <string>
#include <vector>

using namespace std;

#ifndef GSTWELEMENTFACTORY_H
#define GSTWELEMENTFACTORY_H

class GSTWElementFactory
{
public:
    GSTWElementFactory(string elementFactoryName);
    ~GSTWElementFactory();

    string ElementFactoryName;
    GstElementFactory *_GstFactory;
    GstElement *CreateElement(string friendlyName);
    string GetLongName();
    bool GetStaticPadTemplates(GSTWStaticPadTemplate** staticTemplate);
};

#endif
