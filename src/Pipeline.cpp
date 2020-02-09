#include "Pipeline.h"

GSTWPipeline::GSTWPipeline(string pipelineName)
{
  this->PipeLineName = pipelineName;
  this->_GstElement = gst_pipeline_new(pipelineName.c_str());
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

void GSTWPipeline::AddElement(GSTWElement *element)
{
  gst_bin_add(GST_BIN(this->_GstElement), element->_GstElement);
}

void GSTWPipeline::AddMessageHandler(GSTWMessageHandler *messageHandler)
{
  this->MessageHandlers.push_back(messageHandler);
}

void GSTWPipeline::WaitUntilEnd()
{
  this->WaitUntilEnd(GST_CLOCK_TIME_NONE);
}

void GSTWPipeline::WaitUntilEnd(guint64 timeout)
{
  if (timeout != GST_CLOCK_TIME_NONE)
  {
    timeout = timeout * GST_MSECOND;
  }

  GSTWBus *bus = this->GetBus();

  bool terminate = false;

  do
  {
    GSTWMessage *message = bus->GetMessage(timeout);

    if (message != nullptr)
    {
      for (int index = 0; index < this->MessageHandlers.size(); index++)
      {
        GSTWMessageHandler *handler = this->MessageHandlers[index];

        switch (GST_MESSAGE_TYPE(message->_GstMessage))
        {
        case GST_MESSAGE_STATE_CHANGED:
          handler->HandleStateChanged(message);
          break;
        case GST_MESSAGE_ERROR:
          handler->HandleError(message);
          terminate = true;
          break;
        case GST_MESSAGE_EOS:
          handler->HandleEOS(message);
          terminate = true;
          break;
        }
      }
      delete message;
    }
    else if (timeout != GST_CLOCK_TIME_NONE)
    {
      for (int index = 0; index < this->MessageHandlers.size(); index++)
      {
        GSTWMessageHandler *handler = this->MessageHandlers[index];
        handler->HandleTimeout();
      }
    }

  } while (!terminate);

  delete bus;
}

void GSTWPipeline::Play()
{
  gst_element_set_state(this->_GstElement, GST_STATE_PLAYING);
}

void GSTWPipeline::Stop()
{
  gst_element_set_state(this->_GstElement, GST_STATE_NULL);
}
