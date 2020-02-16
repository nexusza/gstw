#include "gst/gst.h"
#include "Message.h"

GSTWMessage::GSTWMessage(GstMessage* message, bool unrefMessage)
{
    this->unrefMessage = unrefMessage;
    this->_GstMessage = message;
}

GSTWMessage::~GSTWMessage()
{
    if(this->unrefMessage && this->_GstMessage != nullptr)
    {
        gst_message_unref (this->_GstMessage);
    }
    
    this->_GstMessage = nullptr;
}

void GSTWMessage::LoadStateChangedStates()
{
    gst_message_parse_state_changed(this->_GstMessage, &this->OldState, &this->NewState, &this->PendingState);
}

string GSTWMessage::GetMessageName()
{
    return gst_structure_get_name (gst_message_get_structure (this->_GstMessage));
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