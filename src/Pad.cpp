#include "Pad.h"

GSTWPad::GSTWPad(string padName)
{
    this->PadName = padName;
    this->_GstPad = nullptr;
}

GSTWPad::~GSTWPad()
{
    if (this->_GstPad != nullptr)
    {
        gst_object_unref(this->_GstPad);
        this->_GstPad = nullptr;
    }
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

void GSTWPad::LinkPad(GSTWPad *pad)
{
    if (gst_pad_link(this->_GstPad, pad->_GstPad) != GST_PAD_LINK_OK)
    {
        g_printerr("Pad could not be linked.\n");
    }
}

void GSTWPad::LinkSourcePad(GstElement *_gstSourceElement, GstPad *_gstSourcePad, string padType)
{
    GstPadLinkReturn ret;
    GstCaps *new_pad_caps = NULL;
    GstStructure *new_pad_struct = NULL;
    const gchar *new_pad_type = NULL;

    padType = "video/x-h264";
    
    g_print("Received new pad '%s' from '%s':\n", GST_PAD_NAME(_gstSourcePad), GST_ELEMENT_NAME(_gstSourceElement));

    /* If our converter is already linked, we have nothing to do here */
    if (gst_pad_is_linked(this->_GstPad))
    {
        g_print("We are already linked. Ignoring.\n");
        goto exit;
    }

    /* Check the new pad's type */
    new_pad_caps = gst_pad_get_current_caps(_gstSourcePad);
    new_pad_struct = gst_caps_get_structure(new_pad_caps, 0);
    new_pad_type = gst_structure_get_name(new_pad_struct);
    if (!g_str_has_prefix(new_pad_type, padType.c_str()))
    {
        g_print("It has type '%s' which is not '%s'. Ignoring.\n", new_pad_type, padType.c_str());
        goto exit;
    }

    /* Attempt the link */
    ret = gst_pad_link(_gstSourcePad, this->_GstPad);

    if (GST_PAD_LINK_FAILED(ret))
    {
        g_print("Type is '%s' but link failed.\n", new_pad_type);
    }
    else
    {
        g_print("Link succeeded (type '%s').\n", new_pad_type);
    }

exit:
    /* Unreference the new pad's caps, if we got them */
    if (new_pad_caps != NULL)
        gst_caps_unref(new_pad_caps);
}

/*
void GSTWPad::LinkSourcePad(GstElement *_gstSourceElement, GstPad *_gstSourcePad, string requestedPadName)
{
    //If our converter is already linked, we have nothing to do here 
    if (gst_pad_is_linked(this->_GstPad))
    {
        g_print("We are already linked. Ignoring.\n");
        return;
    }

    string padName = GST_PAD_NAME(_gstSourcePad);

    if(padName != requestedPadName) {
        g_print("Received new pad '%s' from '%s' which is not '%s':\n", padName.c_str(), GST_ELEMENT_NAME(_gstSourceElement), requestedPadName.c_str());
        return;
    }

g_print("Going 1");

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

g_print("Going 2");

    // Attempt the link
    ret = gst_pad_link(_gstSourcePad, this->_GstPad);

g_print("Going 3");
    if (GST_PAD_LINK_FAILED(ret))
    {
        g_print("Type is '%s' but link failed from source element '%s'.\n", new_pad_type, GST_ELEMENT_NAME(_gstSourceElement));
    }
    else
    {
        g_print("Type is '%s' link succeeded from source element '%s'.\n", new_pad_type, GST_ELEMENT_NAME(_gstSourceElement));
    }

g_print("Going 4");
    gst_caps_unref(new_pad_caps);
    g_print("Going 5");
}*/