#include "Element.h"

#ifndef GSTWNVTRACKER_H
#define GSTWNVTRACKER_H

class GSTWNvTracker : public GSTWElement
{
private:
    /* data */
public:
    GSTWNvTracker(string friendlyName);
    ~GSTWNvTracker();
    void SetWidth(gint value);
    void SetHeight(gint value);
    void SetGpuId(guint value);
    void SetLLConfigFile(string value);
    void SetLLLibFile(string value);
    void SetEnableBatchProcessing(gboolean value);
};

#endif