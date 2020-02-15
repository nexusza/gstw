#include "CustomPipeline.h"

GSTWCustomPipeline::GSTWCustomPipeline(string pipelineName) : GSTWPipeline(pipelineName, pipelineName)
{
}

GSTWCustomPipeline::~GSTWCustomPipeline()
{
}

void GSTWCustomPipeline::CreateElement()
{
    this->_GstElement = gst_pipeline_new(this->FriendlyName.c_str());
}