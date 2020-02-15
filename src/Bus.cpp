#include "Bus.h"

GSTWBus::GSTWBus(GstBus *bus)
{
    this->_GstBus = bus;
}

GSTWBus::~GSTWBus()
{
    gst_object_unref(this->_GstBus);
    this->_GstBus = nullptr;
}

GSTWMessage *GSTWBus::GetMessage(int timeout)
{
    GstMessage *message = gst_bus_timed_pop_filtered(this->_GstBus,
                                                     timeout,
                                                     (GstMessageType)(
                                                         GstMessageType::GST_MESSAGE_STATE_CHANGED |
                                                         GstMessageType::GST_MESSAGE_EOS |
                                                         GstMessageType::GST_MESSAGE_ERROR));

    if (message == nullptr)
    {
        return nullptr;
    }

    return new GSTWMessage(message, true);
}

void GSTWBus::AddMessageHandler(GSTWBusMessageHandler *handler)
{
    this->Handlers.push_back(handler);
}

void GSTWBus::HandleError(GSTWMessage *message)
{
    int handlerSize = this->Handlers.size();

    for (int index = 0; index < handlerSize; index++)
    {
        GSTWBusMessageHandler *handler = this->Handlers[index];
        handler->HandleError(this->_GstBus, message);
    }
}

void GSTWBus::HandleOther(GSTWMessage *message)
{
    int handlerSize = this->Handlers.size();

    for (int index = 0; index < handlerSize; index++)
    {
        GSTWBusMessageHandler *handler = this->Handlers[index];
        handler->HandleOther(this->_GstBus, message);
    }
}

void GSTWBus::HandleStateChanged(GSTWMessage *message)
{
    message->LoadStateChangedStates();

    int handlerSize = this->Handlers.size();

    for (int index = 0; index < handlerSize; index++)
    {
        GSTWBusMessageHandler *handler = this->Handlers[index];
        handler->HandleStateChanged(this->_GstBus, message);
    }
}

void GSTWBus::HandleEOS(GSTWMessage *message)
{
    int handlerSize = this->Handlers.size();

    for (int index = 0; index < handlerSize; index++)
    {
        GSTWBusMessageHandler *handler = this->Handlers[index];
        handler->HandleEOS(this->_GstBus, message);
    }
}

void GSTWBus::HandleApplication(GSTWMessage *message)
{
    int handlerSize = this->Handlers.size();

    for (int index = 0; index < handlerSize; index++)
    {
        GSTWBusMessageHandler *handler = this->Handlers[index];
        handler->HandleApplication(this->_GstBus, message);
    }
}

void GSTWBus::HandleTimeout()
{
    int handlerSize = this->Handlers.size();

    for (int index = 0; index < handlerSize; index++)
    {
        GSTWBusMessageHandler *handler = this->Handlers[index];
        handler->HandleTimeout();
    }
}

void GSTWBus::HandleDurationChange(GSTWMessage *message)
{
    int handlerSize = this->Handlers.size();

    for (int index = 0; index < handlerSize; index++)
    {
        GSTWBusMessageHandler *handler = this->Handlers[index];
        handler->HandleDurationChange(this->_GstBus, message);
    }
}

void GSTWBus::BeginWatch()
{
    gst_bus_add_signal_watch(this->_GstBus);
    //g_signal_connect(G_OBJECT(this->_GstBus), "message::error", (GCallback)bus_error, this);
    //g_signal_connect(G_OBJECT(this->_GstBus), "message::eos", (GCallback)bus_eos, this);
    g_signal_connect(G_OBJECT(this->_GstBus), "message::state-changed", (GCallback)bus_state_changed, this);
    //g_signal_connect(G_OBJECT(this->_GstBus), "message::application", (GCallback)bus_application, this);
}

void GSTWBus::BeginWait()
{
    this->BeginWait(GST_CLOCK_TIME_NONE);
}

void GSTWBus::BeginWait(guint64 timeout)
{
    if (timeout != GST_CLOCK_TIME_NONE)
    {
        timeout = timeout * GST_MSECOND;
    }

    bool terminate = false;

    do
    {
        GSTWMessage *message = this->GetMessage(timeout);

        if (message != nullptr)
        {
            switch (GST_MESSAGE_TYPE(message->_GstMessage))
            {
            case GST_MESSAGE_STATE_CHANGED:
            {
                this->HandleStateChanged(message);
                break;
            }
            case GST_MESSAGE_ERROR:
                this->HandleError(message);
                terminate = true;
                break;
            case GST_MESSAGE_EOS:
                this->HandleEOS(message);
                terminate = true;
                break;
            }

            delete message;
        }
        else if (timeout != GST_CLOCK_TIME_NONE)
        {
            this->HandleTimeout();
        }

    } while (!terminate);
}

static void bus_error(GstBus *_gstBus, GstMessage *_gstMessage, GSTWBus *bus)
{
    GSTWMessage *message = new GSTWMessage(_gstMessage, false);

    bus->HandleError(message);

    delete message;
}

static void bus_eos(GstBus *_gstBus, GstMessage *_gstMessage, GSTWBus *bus)
{
    GSTWMessage *message = new GSTWMessage(_gstMessage, false);

    bus->HandleEOS(message);

    delete message;
}

static void bus_state_changed(GstBus *_gstBus, GstMessage *_gstMessage, GSTWBus *bus)
{
    GSTWMessage *message = new GSTWMessage(_gstMessage, false);

    bus->HandleStateChanged(message);

    delete message;
}

static void bus_application(GstBus *_gstBus, GstMessage *_gstMessage, GSTWBus *bus)
{
    GSTWMessage *message = new GSTWMessage(_gstMessage, false);

    bus->HandleApplication(message);

    delete message;
}

GSTWBusMessageHandler::GSTWBusMessageHandler()
{
}

GSTWBusMessageHandler::~GSTWBusMessageHandler()
{
}

void GSTWBusMessageHandler::HandleError(GstBus *_gstBus, GSTWMessage *message)
{
    this->OnHandleError(_gstBus, message);
}

void GSTWBusMessageHandler::HandleOther(GstBus *_gstBus, GSTWMessage *message)
{
    this->OnHandleOther(_gstBus, message);
}

void GSTWBusMessageHandler::HandleStateChanged(GstBus *_gstBus, GSTWMessage *message)
{
    this->OnHandleStateChanged(_gstBus, message);
}

void GSTWBusMessageHandler::HandleEOS(GstBus *_gstBus, GSTWMessage *message)
{
    this->OnHandleEOS(_gstBus, message);
}

void GSTWBusMessageHandler::HandleApplication(GstBus *_gstBus, GSTWMessage *message)
{
    this->OnHandleApplication(_gstBus, message);
}

void GSTWBusMessageHandler::HandleTimeout()
{
    this->OnHandleTimeout();
}

void GSTWBusMessageHandler::HandleDurationChange(GstBus *_gstBus, GSTWMessage *message)
{
    this->OnHandleDurationChange(_gstBus, message);
}

void GSTWBusMessageHandler::OnHandleError(GstBus *_gstBus, GSTWMessage *message)
{
}

void GSTWBusMessageHandler::OnHandleOther(GstBus *_gstBus, GSTWMessage *message)
{
}

void GSTWBusMessageHandler::OnHandleStateChanged(GstBus *_gstBus, GSTWMessage *message)
{
}

void GSTWBusMessageHandler::OnHandleEOS(GstBus *_gstBus, GSTWMessage *message)
{
}

void GSTWBusMessageHandler::OnHandleApplication(GstBus *_gstBus, GSTWMessage *message)
{
}

void GSTWBusMessageHandler::OnHandleTimeout()
{
}

void GSTWBusMessageHandler::OnHandleDurationChange(GstBus *_gstBus, GSTWMessage *message)
{
}