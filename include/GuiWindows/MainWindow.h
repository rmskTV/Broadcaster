//
// Created by Руслан Москвитин on 21.09.2024.
//

#pragma once

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/splitter.h>
#include <wx/icon.h>
#include <wx/bitmap.h>


#include "../Models/BroadcastedServiceModel.h"
/// @brief Класс главного окна программы
/// @authors Ruslan Moskvitin
/// @date сентябрь 2024
class MainWindow final : public wxFrame
{
public:
    explicit MainWindow(wxWindow* parent);
    ~MainWindow() override;
    /// @brief Добавляет на главный экран программы вкладку транслируемого сервиса (телеканала)
    /// @param [in] broadcastedService экземпляр класса BroadcasterService
    /// @return wxScrolledWindow
    wxScrolledWindow appendServiceToTab(BroadcastedService* broadcastedService);
protected:
private:
    wxNotebook* сhannelsSwitcher;
};