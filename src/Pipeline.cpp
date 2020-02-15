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
        int handlerSize = this->MessageHandlers.size();

        if (message != nullptr)
        {
            switch (GST_MESSAGE_TYPE(message->_GstMessage))
            {
            case GST_MESSAGE_STATE_CHANGED:
            {
                message->LoadStateChangedStates();

                for (int index = 0; index < handlerSize; index++)
                {
                    GSTWMessageHandler *handler = this->MessageHandlers[index];
                    handler->HandleStateChanged(message);
                }

                break;
            }
            case GST_MESSAGE_ERROR:
                for (int index = 0; index < handlerSize; index++)
                {
                    GSTWMessageHandler *handler = this->MessageHandlers[index];
                    handler->HandleError(message);
                }
                terminate = true;
                break;
            case GST_MESSAGE_EOS:
                for (int index = 0; index < handlerSize; index++)
                {
                    GSTWMessageHandler *handler = this->MessageHandlers[index];
                    handler->HandleEOS(message);
                }
                terminate = true;
                break;
            }

            delete message;
        }
        else if (timeout != GST_CLOCK_TIME_NONE)
        {
            for (int index = 0; index < handlerSize; index++)
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
