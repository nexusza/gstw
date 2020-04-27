#include "Element.h"
#include "PadLinkEventHandler.h"

#ifndef GSTWQTDEMUX_H
#define GSTWQTDEMUX_H

class GSTWQtDemux : public GSTWElement
{
private:
    /* data */
public:
    GSTWQtDemux(string friendlyName);
    ~GSTWQtDemux();

    GSTWPadLinkEventHandler* RegisterVideoPad(GSTWElement* element);
};

#endif