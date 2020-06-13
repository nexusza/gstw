#include "gst/gst.h"
#include "Element.h"

#ifndef GSTWCHILDADDEDSIGNALHANDLER_H
#define GSTWCHILDADDEDSIGNALHANDLER_H

struct NameFilter
{
public:
    string Name;
    bool UseRegex;
};

class GSTWChildAddedSignalHandler : public GSTWSignalHandler
{
private:
    int currentFilterIndex = 0;
    vector<NameFilter> filters;
    bool HandleChild(GObject * object, string name);
    bool FilterSatisfied();
public:
    GSTWChildAddedSignalHandler();
    ~GSTWChildAddedSignalHandler();
    void AddNameFilter(string name);    
    void AddRegexNameFilter(string name);    
    void ConnectToSignal(GSTWElement* element);
    void HandleChildAddedSignal(GstChildProxy* self, GObject * object, string name);
protected:
    virtual void OnHandleChildAddedSignal(GSTWElement* element, string name) = 0;
};

static void gstw_child_added_signal(GstChildProxy * self, GObject * object, gchar * name, gpointer user_data);

#endif
