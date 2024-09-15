
//
// Created by Руслан Москвитин on 15.09.2024.
#pragma once

#define PROGRAM_NAME "Broadcaster"
#define FileDescription "Broadcasting authomatisation programm"


#include <wx/wx.h>             // for initialization of wxWidgets
#include <gst/gst.h>          // Uncomment this line for GStreamer


class MyApp : public wxApp
{
public:

    MyApp();
    ~MyApp();

public:
    virtual bool OnInit();
};

DECLARE_APP(MyApp);