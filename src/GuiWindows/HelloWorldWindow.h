//
// Created by Руслан Москвитин on 15.09.2024.
//

#ifndef HELLOWORLDWINDOW_H
#define HELLOWORLDWINDOW_H


#pragma once

#include <wx/wx.h>
#include <wx/tglbtn.h>
#include <gst/gst.h>          // Uncomment this line for GStreamer
#include <gst/video/videooverlay.h>



class HelloWorldWindow: public wxFrame
{
public:
    HelloWorldWindow(wxWindow* parent);
    virtual ~HelloWorldWindow();
protected:
    void OnmnuAbout(wxCommandEvent& event);
private:
    wxStatusBar* stb;
    wxMenuBar* mnuBar;
    wxPanel* m_panel;
    wxWindow* m_renderWindow;

    // GStreamer data
    GstElement* m_pipeline;
    guintptr m_xid;
    gint flags;

};



#endif //HELLOWORLDWINDOW_H
