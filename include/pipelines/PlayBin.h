#include "gst/gst.h"
#include "Pipeline.h"
#include "ObjectProperties.h"

#ifndef GSTWPLAYBIN_H
#define GSTWPLAYBIN_H

class GSTWPlayBin : public GSTWPipeline
{
private:
    GSTWObjectProperties* uri;
public:
    GSTWPlayBin(string friendlyName);
    ~GSTWPlayBin();

    GSTWObjectProperties* Uri();
};

#endif