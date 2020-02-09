#include "Pad.h"

GSTWPad::GSTWPad(GstElement* _gstElement, string padName)
{
    this->_GstPad = gst_element_get_static_pad (_gstElement, padName.c_str());
    //this->_GstElement = _gstElement;
}

GSTWPad::~GSTWPad()
{
      gst_object_unref(this->_GstPad);
      this->_GstPad = nullptr;
      //this->_GstElement = nullptr;
}

void GSTWPad::LinkSourcePad(GstElement* _gstSourceElement, GstPad* _gstSourcePad)
{
    GstPadLinkReturn ret;
    GstCaps *new_pad_caps = NULL;
    GstStructure *new_pad_struct = NULL;
    const gchar *new_pad_type = NULL;

    g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (_gstSourcePad), GST_ELEMENT_NAME (_gstSourceElement));

    /* If our converter is already linked, we have nothing to do here */
    if (gst_pad_is_linked (this->_GstPad)) {
        g_print ("We are already linked. Ignoring.\n");
        goto exit;
    }

    /* Check the new pad's type */
    new_pad_caps = gst_pad_get_current_caps (_gstSourcePad);
    new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
    new_pad_type = gst_structure_get_name (new_pad_struct);
    if (!g_str_has_prefix (new_pad_type, "audio/x-raw")) {
        g_print ("It has type '%s' which is not raw audio. Ignoring.\n", new_pad_type);
        goto exit;
    }

    /* Attempt the link */
    ret = gst_pad_link (_gstSourcePad, this->_GstPad);

    if (GST_PAD_LINK_FAILED (ret)) {
        g_print ("Type is '%s' but link failed.\n", new_pad_type);
    } else {
        g_print ("Link succeeded (type '%s').\n", new_pad_type);
    }

    exit:
    /* Unreference the new pad's caps, if we got them */
    if (new_pad_caps != NULL)
        gst_caps_unref (new_pad_caps);   
}