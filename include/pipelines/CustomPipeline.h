#include "Pipeline.h"

#ifndef GSTWCUSTOMPIPELINE_H
#define GSTWCUSTOMPIPELINE_H

class GSTWCustomPipeline : public GSTWPipeline
{
private:
    /* data */
public:
    GSTWCustomPipeline(string pipelineName);
    ~GSTWCustomPipeline();
    void CreateElement();
};

#endif