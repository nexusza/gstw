#include "Element.h"

#ifndef GSTWNVINFER_H
#define GSTWNVINFER_H

class GSTWNvInfer : public GSTWElement
{
private:
    /* data */
public:
    GSTWNvInfer(string friendlyName);
    ~GSTWNvInfer();
    void SetConfigFilePath(string value);
};

#endif