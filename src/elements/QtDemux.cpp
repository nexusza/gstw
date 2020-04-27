#include "QtDemux.h"

GSTWQtDemux::GSTWQtDemux(string friendlyName) : GSTWElement("qtdemux", friendlyName)
{
}

GSTWQtDemux::~GSTWQtDemux()
{
}

GSTWPadLinkEventHandler* GSTWQtDemux::RegisterVideoPad(GSTWElement* element)
{
    GSTWPadLinkEventHandler* padAdded = new GSTWPadLinkEventHandler(element, "video_0");
    padAdded->ConnectToPadAddedSignal(this);
    return padAdded;
}