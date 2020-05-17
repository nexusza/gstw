#include "NvInfer.h"

GSTWNvInfer::GSTWNvInfer(string friendlyName) : GSTWElement("nvinfer", friendlyName)
{
}

GSTWNvInfer::~GSTWNvInfer()
{
}

void GSTWNvInfer::SetConfigFilePath(string value)
{
g_object_set (this->_GstElement, "config-file-path", value.c_str(), NULL);
}