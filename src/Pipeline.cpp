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

GstStateChangeReturn GSTWPipeline::SetToReadyState()
{
    return gst_element_set_state(this->_GstElement, GST_STATE_READY);
}

GstStateChangeReturn GSTWPipeline::SetToPlayingState()
{
    return gst_element_set_state(this->_GstElement, GST_STATE_PLAYING);
}

GstStateChangeReturn GSTWPipeline::SetToPausedState()
{
    return gst_element_set_state(this->_GstElement, GST_STATE_PAUSED);
}

GstStateChangeReturn GSTWPipeline::SetToNullState()
{
    return gst_element_set_state(this->_GstElement, GST_STATE_NULL);
}


void GSTWPipeline::ResetClock()
{
    this->SetToPausedState();
    this->SetToPlayingState();
}
