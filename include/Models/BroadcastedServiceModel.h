//
// Created by Руслан Москвитин on 21.09.2024.
//

#ifndef BROADCASTEDSERVICE_H
#define BROADCASTEDSERVICE_H

/// @brief Класс транслируемого сервиса (телеканала)
/// @authors Ruslan Moskvitin
/// @date сентябрь 2024
class BroadcastedService {

    private:
     ///@brief Наименование сервиса
     wxString name_;
     ///@brief Вкладка в главном окне программы, в которой ведется работа с сервисом
     wxScrolledWindow *guiMainWIndowPanel = nullptr;

    public:
    ///@brief Получить наименование сервиса
    wxString getName(){return name_;}
    ///@brief Изменить наименование сервиса
    void setName(wxString name){this->name_ = name;}

};



#endif //BROADCASTEDSERVICE_H
