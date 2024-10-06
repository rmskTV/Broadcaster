//
// Created by Руслан Москвитин on 21.09.2024.
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/splitter.h>
#include <wx/icon.h>
#include <wx/bitmap.h>

#include "../Models/Channel.h"
/// @brief Класс главного окна программы
/// @authors Ruslan Moskvitin
/// @date Сентябрь 2024
class MainWindow final : public wxFrame
{
public:
    explicit MainWindow(wxWindow* parent);
    ~MainWindow() override;
    /// @brief Добавляет на главный экран программы вкладку транслируемого сервиса (телеканала)
    /// @param [in] broadcastedService экземпляр класса BroadcasterService
    /// @return wxScrolledWindow
    wxScrolledWindow appendServiceToTab(Channel* broadcastedService);
protected:
private:
    wxNotebook* сhannelsSwitcher;
};
#endif //MAINWINDOW_H