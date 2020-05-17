#include "gst/gst.h"
#include "Pad.h"

#ifndef GSTWPADPROBEHANDLER_H
#define GSTWPADPROBEHANDLER_H

class GSTWPadProbeHandler
{
protected:
    virtual void OnHandlePadProbe(GstPad* pad, GstPadProbeInfo * info);
public:
    void HandlePadProbe(GstPad* pad, GstPadProbeInfo * info);
};

#endif