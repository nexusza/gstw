#include "gst/gst.h"
#include "Capabilities.h"
#include <vector>

using namespace std;

#ifndef GSTWSTATICPADTEMPLATE_H
#define GSTWSTATICPADTEMPLATE_H

class GSTWStaticPadTemplate
{
private:
    const GList *_glist;

public:
    GSTWStaticPadTemplate(const GList *_list);
    ~GSTWStaticPadTemplate();
    GstStaticPadTemplate *_GstStaticPadTemplate;
    bool GetCapabilities(GSTWCapabilities **capabilities);
    bool GetNextTemplate(GSTWStaticPadTemplate **staticTemplate);
    static bool GetStaticPadTemplates(GstElementFactory *_gstFactory, GSTWStaticPadTemplate **staticTemplate);
};

#endif
