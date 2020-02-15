#include "gst/gst.h"
#include "Bin.h"
#include "MessageHandler.h"
#include "Bus.h"
#include <string>
#include <vector>

using namespace std;

#ifndef GSTWPIPELINE_H
#define GSTWPIPELINE_H

class GSTWPipeline : public GSTWBin
{
    
public:
    GSTWPipeline(string elementName, string friendlyName);
    ~GSTWPipeline();

    vector<GSTWMessageHandler*> MessageHandlers;

    void AddMessageHandler(GSTWMessageHandler* messageHandlers);
    
    void Play();
    void WaitUntilEnd(guint64 timeout);
    void WaitUntilEnd();
    void Stop();
    GSTWBus* GetBus();
};

#endif