#include "gst/gst.h"
#include "Element.h"
#include "ChildAddedSignalHandler.h"
#include <regex> 
  
using namespace std; 

GSTWChildAddedSignalHandler::GSTWChildAddedSignalHandler()
{
}

GSTWChildAddedSignalHandler::~GSTWChildAddedSignalHandler()
{
}

void GSTWChildAddedSignalHandler::ConnectToSignal(GSTWElement* element)
{
    g_signal_connect(element->_GstElement, "child-added", G_CALLBACK(gstw_child_added_signal), this);
}

bool GSTWChildAddedSignalHandler::HandleChild(GObject * object, string name)
{
    NameFilter filter = this->filters[this->currentFilterIndex];

    if(filter.UseRegex)
    {
        if(regex_match(name, regex(filter.Name)))
        {
            this->currentFilterIndex++;
            return true;
        }

        //g_print("Regex filter '%s' failed for name '%s'.\n", filter.Name.c_str(), name.c_str());
    }
    else
    {
        if(name == filter.Name)
        {
            this->currentFilterIndex++;
            return true;
        }
    }

    return false;
}

bool GSTWChildAddedSignalHandler::FilterSatisfied()
{
    return this->currentFilterIndex >= this->filters.size();
}

void GSTWChildAddedSignalHandler::HandleChildAddedSignal(GstChildProxy * self, GObject * object, string name)
{
    if(this->HandleChild(object, name))
    {
        if(!this->FilterSatisfied())
        {
            g_print("Found child element '%s'. Continuing filter.\n", name.c_str());
            g_signal_connect(G_OBJECT(object), "child-added", G_CALLBACK(gstw_child_added_signal), this);
        }
        else
        {
            g_print("Found child element '%s'.\n", name.c_str());
            
            GSTWElement* element = new GSTWElement((GstElement*)object);

            this->OnHandleChildAddedSignal(element, name);

            delete element;
        }
    }   
    else
    {
        //g_print("Child element '%s' not handled.\n", name.c_str());
    }
}

void GSTWChildAddedSignalHandler::AddNameFilter(string name)
{
    NameFilter filter;
    filter.Name = name;
this->filters.push_back(filter);
}

void GSTWChildAddedSignalHandler::AddRegexNameFilter(string name)
{
    NameFilter filter;
    filter.Name = name;
    filter.UseRegex = true;
 this->filters.push_back(filter);   
}

static void gstw_child_added_signal(GstChildProxy * self, GObject * object, gchar * name, gpointer user_data)
{
    ((GSTWChildAddedSignalHandler*)user_data)->HandleChildAddedSignal(self, object, name);
}