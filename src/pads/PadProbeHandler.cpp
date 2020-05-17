#include "PadProbeHandler.h"

void GSTWPadProbeHandler::HandlePadProbe(GstPad* pad, GstPadProbeInfo * info)
{
    this->OnHandlePadProbe(pad, info);
}

void GSTWPadProbeHandler::OnHandlePadProbe(GstPad* pad, GstPadProbeInfo * info)
{
    
}
