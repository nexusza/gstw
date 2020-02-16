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

void GSTWPipeline::SetToReadyState()
{
    gst_element_set_state(this->_GstElement, GST_STATE_READY);
}

void GSTWPipeline::SetToPlayingState()
{
    gst_element_set_state(this->_GstElement, GST_STATE_PLAYING);
}

void GSTWPipeline::SetToPausedState()
{
    gst_element_set_state(this->_GstElement, GST_STATE_PAUSED);
}

void GSTWPipeline::SetToNullState()
{
    gst_element_set_state(this->_GstElement, GST_STATE_NULL);
}
