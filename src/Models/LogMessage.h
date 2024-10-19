//
// Created by Руслан Москвитин on 06.10.2024.
//

#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H
#pragma once

#include <vector>

#include "Model.h"
enum class LogLevel {INFO, WARNING, ERROR};

class LogMessage : public Model {
    ///@brief Название таблицы для хранения экземпляров модели
    static inline std::string tableName = "log_messages";
    ///@brief Массив полей таблицы
    static std::vector<dbField> dbFields;
    LogLevel _level = LogLevel::INFO;
    std::string _source;
    std::string _message;
public:
    ///@brief Проверяет структуру таблицы. При необходимости создает таблицу и требуемые поля
    static void checkTable() {
        checkTableFor(&tableName, &dbFields);
    }

    static void create(LogLevel level, const std::string& source, const std::string& message);

};



#endif //LOGMESSAGE_H
