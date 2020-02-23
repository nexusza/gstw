#include "WaveScope.h"

GSTWWaveScope::GSTWWaveScope(string friendlyName) : GSTWElement("wavescope", friendlyName)
{
}

GSTWWaveScope::~GSTWWaveScope()
{
}

void GSTWWaveScope::Shader(int value)
{
    g_object_set(this->_GstElement, "shader", value, NULL);
}


void GSTWWaveScope::Style(int value)
{
    g_object_set(this->_GstElement, "style", value, NULL);
}