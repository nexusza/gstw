#include "AppSrc.h"

void GSTWAppSrcChangedEventHandler::HandleNeedData(GstElement *source, guint size)
{
    this->OnHandleNeedData(source, size);
}

void GSTWAppSrcChangedEventHandler::HandleEnoughData(GstElement *source)
{
    this->OnHandleEnoughData(source);
}

void GSTWAppSrcChangedEventHandler::OnHandleNeedData(GstElement *source, guint size)
{
}

void GSTWAppSrcChangedEventHandler::OnHandleEnoughData(GstElement *source)
{
}

GSTWAppSrc::GSTWAppSrc(string friendlyName) : GSTWElement("appsrc", friendlyName)
{
}

GSTWAppSrc::~GSTWAppSrc()
{
}

void GSTWAppSrc::SetCaps(GSTWCapabilities *caps)
{
    g_object_set(this->_GstElement, "caps", caps->_GstCaps, NULL);
}

void GSTWAppSrc::SetFormat(GstFormat format)
{
    g_object_set(this->_GstElement, "format", format, NULL);
}

GstFlowReturn GSTWAppSrc::EmitPushBuffer(GSTWBuffer *buffer)
{
    GstFlowReturn result;
    g_signal_emit_by_name (this->_GstElement, "push-buffer", buffer->_gstBuffer, &result);
    return result;
}

void GSTWAppSrc::OnNeedData(GSTWAppSrcChangedEventHandler *handler)
{
    g_signal_connect(this->_GstElement, "need-data", G_CALLBACK(appsrc_need_data), handler);
}

void GSTWAppSrc::OnEnoughData(GSTWAppSrcChangedEventHandler *handler)
{
    g_signal_connect(this->_GstElement, "enough-data", G_CALLBACK(appsrc_enough_data), handler);
}

void appsrc_need_data(GstElement *source, guint size, GSTWAppSrcChangedEventHandler *handler)
{
    handler->HandleNeedData(source, size);
}

void appsrc_enough_data(GstElement *source, GSTWAppSrcChangedEventHandler *handler)
{
    handler->HandleEnoughData(source);
}