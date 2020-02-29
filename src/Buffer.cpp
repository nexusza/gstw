#include "Buffer.h"

GSTWBuffer::GSTWBuffer()
{
    this->_gstBuffer = nullptr;
}

GSTWBuffer::~GSTWBuffer()
{
    if (this->_gstBuffer != nullptr)
    {
        gst_buffer_unref(this->_gstBuffer);
        this->_gstBuffer = nullptr;
    }
}

void GSTWBuffer::CreateBuffer(gsize size)
{
    this->_gstBuffer = gst_buffer_new_and_alloc(size);
}

void GSTWBuffer::SetTimestamp(guint64 val, guint64 num, guint64 denom)
{
    GST_BUFFER_TIMESTAMP(this->_gstBuffer) = gst_util_uint64_scale(val, num, denom);
}

void GSTWBuffer::SetDuration(guint64 val, guint64 num, guint64 denom)
{
    GST_BUFFER_DURATION(this->_gstBuffer) = gst_util_uint64_scale(val, num, denom);
}