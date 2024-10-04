//
// Created by Руслан Москвитин on 30.09.2024.
//

#ifndef BROADCASTEDSERVICE_H
#define BROADCASTEDSERVICE_H

#include <wx/wx.h>

#include "Model.h"


/// @brief Класс транслируемого сервиса (телеканала)
/// @authors Ruslan Moskvitin
/// @date сентябрь 2024
class BroadcastedService : public Model{

private:
    ///@brief Наименование сервиса
    wxString _name;
    ///@brief Вкладка в главном окне программы, в которой ведется работа с сервисом
    wxScrolledWindow *guiMainWIndowPanel = nullptr;

public:
    ///@brief Получить наименование сервиса
    wxString getName(){return _name;}
    ///@brief Изменить наименование сервиса
    void setName(wxString name){this->_name = name;}

};

#endif //BROADCASTEDSERVICE_H
