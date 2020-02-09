#include "MessageHandler.h"

GSTWMessageHandler::GSTWMessageHandler()
{
}

GSTWMessageHandler::~GSTWMessageHandler()
{
}

void GSTWMessageHandler::HandleError(GSTWMessage *message)
{
    this->OnHandleError(message);
}

void GSTWMessageHandler::HandleOther(GSTWMessage *message)
{
    this->OnHandleOther(message);
}

void GSTWMessageHandler::HandleStateChanged(GSTWMessage *message)
{
    this->OnHandleStateChanged(message);
}

void GSTWMessageHandler::HandleEOS(GSTWMessage *message)
{
    this->OnHandleEOS(message);
}

void GSTWMessageHandler::HandleTimeout()
{
    this->OnHandleTimeout();
}

void GSTWMessageHandler::HandleDurationChange(GSTWMessage *message)
{
    this->OnHandleDurationChange(message);
}

void GSTWMessageHandler::OnHandleError(GSTWMessage *message)
{
}

void GSTWMessageHandler::OnHandleOther(GSTWMessage *message)
{
}

void GSTWMessageHandler::OnHandleStateChanged(GSTWMessage *message)
{
}

void GSTWMessageHandler::OnHandleEOS(GSTWMessage *message)
{
}

void GSTWMessageHandler::OnHandleTimeout()
{
}

void GSTWMessageHandler::OnHandleDurationChange(GSTWMessage *message)
{
}