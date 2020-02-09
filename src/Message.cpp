#include "Message.h"

GSTWMessage::GSTWMessage(GstMessage* message)
{
    this->_GstMessage = message;
    gst_message_parse_state_changed (message, &this->OldState, &this->NewState, &this->PendingState);
}

GSTWMessage::~GSTWMessage()
{
    gst_message_unref (this->_GstMessage);
    this->_GstMessage = NULL;
}

gboolean GSTWMessage::IsForElement(GstElement* element)
{
    return GST_MESSAGE_SRC (this->_GstMessage) == GST_OBJECT (element);
}

gboolean GSTWMessage::IsInState(GstState state)
{
    return this->NewState == state;
}

gboolean GSTWMessage::IsPlaying()
{
    return this->IsInState(GstState::GST_STATE_PLAYING);
}

gboolean GSTWMessage::IsPaused()
{
    return this->IsInState(GstState::GST_STATE_PAUSED);
}