#include "gst/gst.h"
#include "Bin.h"
#include "Bus.h"
#include <string>
#include <vector>

using namespace std;

#ifndef GSTWPIPELINE_H
#define GSTWPIPELINE_H

class GSTWPipeline : public GSTWBin
{
private:

public:
    GSTWPipeline(string elementName, string friendlyName);
    ~GSTWPipeline();
    
    void SetToReadyState();
    void SetToPlayingState();
    void SetToPausedState();
    void SetToNullState();
    GSTWBus* GetBus();
};

#endif