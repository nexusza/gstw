#include "gst/pbutils/pbutils.h"
#include <string>

using namespace std;

#ifndef GSTWDISCOVERER_H
#define GSTWDISCOVERER_H

class GSTWDiscoverer
{
public:
    GSTWDiscoverer(string uri);
    ~GSTWDiscoverer();

    string Uri;
    GstDiscoverer *_GstDiscoverer;
    bool CreateDiscoverer(GstClockTime timeout);
    bool StartDiscoverer();
    void StopDiscoverer();

    virtual void OnDiscovererFinshed();
    virtual void OnDiscovererDiscovered();
};

static void discoverer_discovered(GstDiscoverer *discoverer, GstDiscovererInfo *info, GError *err, GSTWDiscoverer *data);
static void discoverer_finished(GstDiscoverer *discoverer, GSTWDiscoverer *data);

#endif