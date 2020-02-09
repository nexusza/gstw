#include "Bus.h"

GSTWMessage* GSTWBus::GetMessage(int timeout)
{
    GstMessage* message = gst_bus_timed_pop_filtered(this->_GstBus, 
     timeout, 
    (GstMessageType)(GstMessageType::GST_MESSAGE_STATE_CHANGED | GstMessageType::GST_MESSAGE_EOS | GstMessageType::GST_MESSAGE_ERROR));

    if(message == nullptr)
    {
        return nullptr;
    }

    return new GSTWMessage(message);
}

GSTWBus::GSTWBus(GstBus* bus)
{
    this->_GstBus = bus;
}

GSTWBus::~GSTWBus()
{
    gst_object_unref (this->_GstBus);
    this->_GstBus = nullptr; 
}