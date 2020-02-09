#include "ObjectProperties.h"

GSTWObjectProperties::GSTWObjectProperties(GstElement* elemenet, string propertyName)
{
    this->propertyName = propertyName;
    this->_gstElement = elemenet;
}

GSTWObjectProperties::~GSTWObjectProperties()
{
}

void GSTWObjectProperties::Set(string value)
{
    g_object_set(this->_gstElement, this->propertyName.c_str(), value.c_str(), NULL);
}

void GSTWObjectProperties::Set(int value)
{
    g_object_set(this->_gstElement, this->propertyName.c_str(), value, NULL);
}

string GSTWObjectProperties::Get()
{
    //return g_object_get(this->propertyName.c_str());
    return "";
}