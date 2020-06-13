#include "Pad.h"

GSTWPad::GSTWPad()
{
    this->caps = nullptr;
    this->padStructure = nullptr;
}

GSTWPad::~GSTWPad()
{
    if(this->caps != nullptr)
    {
        gst_caps_unref(this->caps);
    }
    
    this->caps = nullptr;
    this->padStructure = nullptr;
}

string GSTWPad::GetPadName()
{
    if(this->padName.empty())
    {
        this->padName = GST_PAD_NAME(this->_GstPad);
    }

    return this->padName;
}

GstCaps* GSTWPad::GetPadCaps()
{
    if(this->caps == nullptr)
    {
        this->caps = gst_pad_get_current_caps(this->_GstPad);
    }
    
    return this->caps;
}

GstStructure* GSTWPad::GetCapsStructure()
{
    if(this->padStructure == nullptr)
    {
        this->padStructure =  gst_caps_get_structure(this->GetPadCaps(), 0);
    }
    
    return this->padStructure;
}

string GSTWPad::GetPadType()
{
    if(this->padType.empty())
    {
        this->padType = gst_structure_get_name(this->GetCapsStructure());
    }
    
    return this->padType;
}

bool GSTWPad::HasFeature(string feature)
{
    GstCapsFeatures *features = gst_caps_get_features (this->GetPadCaps(), 0);

    return gst_caps_features_contains (features, feature.c_str());
}

bool GSTWPad::GetCapabilities(GSTWCapabilities **capabilities)
{
    /* Retrieve negotiated caps (or acceptable caps if negotiation is not finished yet) */
    GstCaps *caps = gst_pad_get_current_caps(this->_GstPad);

    if (!caps)
    {
        caps = gst_pad_query_caps(this->_GstPad, NULL);
    }

    if (caps)
    {
        *capabilities = new GSTWCapabilities(caps);
        return true;
    }

    return false;
}

bool GSTWPad::IsLinked()
{
    return gst_pad_is_linked(this->_GstPad);
}

void GSTWPad::LinkPad(GSTWPad *pad)
{
    if (this->IsLinked())
    {
        g_print("Pad '%s' already linked. Ignoring.\n", this->GetPadName().c_str());
        return;
    }

    if (gst_pad_link(this->_GstPad, pad->_GstPad) != GST_PAD_LINK_OK)
    {
        g_printerr("Pad '%s' could not be linked to pad '%s'.\n", this->GetPadName().c_str(), pad->GetPadName().c_str());
    }
}

void GSTWPad::LinkSourcePad(GstElement *_gstSourceElement, GstPad *_gstSourcePad, string targetElementName, string requestedPadName)
{
    //If our converter is already linked, we have nothing to do here 
    if (gst_pad_is_linked(this->_GstPad))
    {
        g_print("Pad already linked. Ignoring.\n");
        return;
    }

    string padName = GST_PAD_NAME(_gstSourcePad);

    if(padName != requestedPadName) {
        g_print("Received new pad '%s' from '%s' which is not '%s':\n", padName.c_str(), GST_ELEMENT_NAME(_gstSourceElement), requestedPadName.c_str());
        return;
    }

    GstPadLinkReturn ret;
    GstCaps *new_pad_caps = NULL;
    GstStructure *new_pad_struct = NULL;
    const gchar *new_pad_type = NULL;

    //Check the new pad's type
    new_pad_caps = gst_pad_get_current_caps(_gstSourcePad);
    new_pad_struct = gst_caps_get_structure(new_pad_caps, 0);
    new_pad_type = gst_structure_get_name(new_pad_struct);
    //if (!g_str_has_prefix(new_pad_type, padType.c_str()))
    //{
    //    g_print("It has type '%s' which is not '%s'. Ignoring.\n", new_pad_type, padType.c_str());
    //    goto exit;
    //}

    // Attempt the link
    ret = gst_pad_link(_gstSourcePad, this->_GstPad);

    if (GST_PAD_LINK_FAILED(ret))
    {
        g_print("Type is '%s' but link failed from source element '%s' to target element '%s'.\n", new_pad_type, GST_ELEMENT_NAME(_gstSourceElement), targetElementName.c_str());
    }
    else
    {
        g_print("Type is '%s' link succeeded from source element '%s' to target element '%s'.\n", new_pad_type, GST_ELEMENT_NAME(_gstSourceElement), targetElementName.c_str());
    }

    gst_caps_unref(new_pad_caps);
}