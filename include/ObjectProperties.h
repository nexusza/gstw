#include "gst/gst.h"
#include <string>

using std::string;

#ifndef GSTWOBJECTPROPERTIES_H
#define GSTWOBJECTPROPERTIES_H

class GSTWObjectProperties
{
private:
    string propertyName;
    
public:
    GSTWObjectProperties(GstElement* elemenet, string propertyName);
    ~GSTWObjectProperties();
    
    GstElement* _gstElement;
    void Set(string value);
    void Set(int value);
    string Get();
};

#endif