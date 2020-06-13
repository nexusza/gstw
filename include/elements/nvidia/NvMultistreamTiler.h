#include "Element.h"

#ifndef GSTWNVMULTISTREAMTILER_H
#define GSTWNVMULTISTREAMTILER_H

class GSTWNvMultistreamTiler : public GSTWElement
{
private:
    /* data */
public:
    GSTWNvMultistreamTiler(string friendlyName);
    ~GSTWNvMultistreamTiler();
    void SetRowsAndColumns(gint totalSources);
    void SetRows(guint value);
    void SetColumns(guint value);
    void SetHeight(gint value);
    void SetWidth(guint value);
};

#endif