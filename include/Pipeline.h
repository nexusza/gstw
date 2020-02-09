#include "gst/gst.h"
#include "Element.h"
#include "MessageHandler.h"
#include "Bus.h"
#include <string>
#include <vector>

using namespace std;

#ifndef GSTWPIPELINE_H
#define GSTWPIPELINE_H

class GSTWPipeline
{
    
public:
    GSTWPipeline(string pipelineName);
    ~GSTWPipeline();

    string PipeLineName;
    GstElement* _GstElement;
    vector<GSTWMessageHandler*> MessageHandlers;

    void AddMessageHandler(GSTWMessageHandler* messageHandlers);
    void AddElement(GSTWElement* element);
    void Play();
    void WaitUntilEnd(guint64 timeout);
    void WaitUntilEnd();
    void Stop();
    GSTWBus* GetBus();
};

#endif