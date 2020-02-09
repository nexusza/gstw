#include "Pipeline.h"
#include "Element.h"
#include "MessageHandler.h"
#include "SeekQuery.h"

#ifndef GSTWSEEKER_H
#define GSTWSEEKER_H

class GSTWSeeker : public GSTWMessageHandler
{
private:
    /* data */
public:
    GSTWSeeker(GSTWElement* element);
    ~GSTWSeeker();

    void OnHandleDurationChange(GSTWMessage *message);
    void OnHandleStateChanged(GSTWMessage *message);
    void OnHandleTimeout();

    GSTWElement* Element;
    gboolean SeekDone;
    gboolean CanSeek;
    gint64 Duration;
    gint64 Start;
    gint64 End;
};


#endif