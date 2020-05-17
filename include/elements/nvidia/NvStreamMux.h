#include "Element.h"
#include "RequestPad.h"

#ifndef GSTWNVNVSTREAMMUX_H
#define GSTWNVNVSTREAMMUX_H

class GSTWNvStreamMux : public GSTWElement
{
private:
    /* data */
public:
    GSTWNvStreamMux(string friendlyName);
    ~GSTWNvStreamMux();

    void SetWidth(gint value);
    void SetHeight(gint value);
    void SetBatchSize(gint value);
    void SetBatchedPushTimeout(gint value);
    GSTWRequestPad* GetRequestPad();
};

#endif