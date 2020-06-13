#include "NvMultistreamTiler.h"
#include <math.h>

GSTWNvMultistreamTiler::GSTWNvMultistreamTiler(string friendlyName) : GSTWElement("nvmultistreamtiler", friendlyName)
{
}

GSTWNvMultistreamTiler::~GSTWNvMultistreamTiler()
{
}

void GSTWNvMultistreamTiler::SetRowsAndColumns(gint totalSources)
{
    guint tiler_rows = (guint) sqrt (totalSources);
    guint tiler_columns = (guint) ceil (1.0 * totalSources / tiler_rows);
    this->SetRows(tiler_rows);
    this->SetColumns(tiler_columns);
}

void GSTWNvMultistreamTiler::SetRows(guint value)
{
g_object_set (this->_GstElement, "rows", value, NULL);
}

void GSTWNvMultistreamTiler::SetColumns(guint value)
{
g_object_set (this->_GstElement, "columns", value, NULL);
}

void GSTWNvMultistreamTiler::SetHeight(gint value)
{
g_object_set (this->_GstElement, "height", value, NULL);
}

void GSTWNvMultistreamTiler::SetWidth(guint value)
{
g_object_set (this->_GstElement, "width", value, NULL);
}