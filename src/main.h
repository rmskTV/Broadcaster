
//
// Created by Руслан Москвитин on 15.09.2024.
#ifndef MAIN_H
#define MAIN_H
#pragma once

#define PROGRAM_NAME "Broadcaster"
#define FileDescription "Broadcasting authomatisation programm"


#include <wx/wx.h>
#include <gst/gst.h>          // Uncomment this line for GStreamer
#include "GuiWindows/MainWindow.h"

/// @brief Класс main
/// @authors Ruslan Moskvitin
/// @date сентябрь 2024
class MyApp : public wxApp
{
public:

    MyApp();
    ~MyApp();

    virtual bool OnInit();

};

DECLARE_APP(MyApp);
#endif //MAIN_H