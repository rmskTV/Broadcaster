//
// Created by Руслан Москвитин on 30.09.2024.
//

#ifndef CHANNEL_H
#define CHANNEL_H
#pragma once
#include <wx/wx.h>

#include <utility>

#include "../ORM/BaseModel.h"
#include "Model.h"


/// @brief Класс транслируемого сервиса (телеканала)
/// @authors Ruslan Moskvitin
/// @date Сентябрь 2024
class Channel : public Model{
    ///@brief Название таблицы для хранения экземпляров модели
    static inline std::string tableName = "channels";

    ///@brief Массив полей таблицы
    static std::vector<dbField> dbFields;

    ///@brief Наименование сервиса
    wxString _name;

    ///@brief Вкладка в главном окне программы, в которой ведется работа с сервисом
    wxScrolledWindow *guiMainWIndowPanel = nullptr;

public:
    ///@brief Проверяет структуру таблицы. При необходимости создает таблицу и требуемые поля
    static void checkTable(){checkTableFor(&tableName, &dbFields);}

    ///@brief Получить наименование сервиса
    wxString getName(){return _name;}

    ///@brief Изменить наименование сервиса
    void setName(wxString name){this->_name = std::move(name);}
};

#endif //CHANNEL_H
