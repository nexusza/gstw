#include "Pipeline.h"

GSTWPipeline::GSTWPipeline(string elementName, string friendlyName) : GSTWBin(elementName, friendlyName)
{
    
}

GSTWPipeline::~GSTWPipeline()
{
    gst_object_unref(this->_GstElement);
    this->_GstElement = nullptr;
}

GSTWBus *GSTWPipeline::GetBus()
{
    return new GSTWBus(gst_element_get_bus(this->_GstElement));
}

void GSTWPipeline::Play()
{
    gst_element_set_state(this->_GstElement, GST_STATE_PLAYING);
}

void GSTWPipeline::Stop()
{
    gst_element_set_state(this->_GstElement, GST_STATE_NULL);
}
