#include "gst/gst.h"
#include "ElementFactory.h"

GSTWElementFactory::GSTWElementFactory(string elementName)
{
    this->ElementFactoryName = elementName;
    this->_GstFactory = nullptr;
}

GSTWElementFactory::~GSTWElementFactory()
{
    if (this->_GstFactory != nullptr)
    {
        gst_object_unref(this->_GstFactory);
        this->_GstFactory = nullptr;
    }
}

string GSTWElementFactory::GetLongName()
{
    return gst_element_factory_get_longname(this->_GstFactory);
}

GstElement *GSTWElementFactory::CreateElement(string friendlyName)
{
    if (this->_GstFactory == nullptr)
    {
        this->_GstFactory = gst_element_factory_find(this->ElementFactoryName.c_str());
    }

    return gst_element_factory_create(this->_GstFactory, friendlyName.c_str());
}

bool GSTWElementFactory::GetStaticPadTemplates(GSTWStaticPadTemplate **staticTemplate)
{
    if (this->_GstFactory != nullptr)
    {
        return GSTWStaticPadTemplate::GetStaticPadTemplates(this->_GstFactory, staticTemplate);
    }

    return false;
}