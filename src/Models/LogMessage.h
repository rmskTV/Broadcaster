//
// Created by Руслан Москвитин on 06.10.2024.
//

#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H
#pragma once

#include <vector>

#include "Model.h"
#include "../ORM/ModelQueryBuilder.h"

enum class LogLevel {INFO, WARNING, ERROR};

inline const char* indexForLevel(LogLevel level)
{
    switch(level)
    {
        case LogLevel::INFO:         return "0";
        case LogLevel::WARNING:      return "1";
        case LogLevel::ERROR:        return "2";
        default:                     return "3";
    }
}

class LogMessage : public Model {
    ///@brief Название таблицы для хранения экземпляров модели
    static inline std::string tableName = "log_messages";
    ///@brief Массив полей таблицы
    static std::vector<dbField> dbFields;
    LogLevel _level = LogLevel::INFO;
    std::string _source;
    std::string _message;
    static QueryBuilder* newQueryBuilder() {
        return ModelQueryBuilder<LogMessage>::query();
    }
public:
    ///@brief  Возвращает название ассоциированной таблицы
    const static std::string& getTableName() {return tableName;}

    ///@brief  Возвращает список полей
    static std::vector<dbField>* getDbFields() {return &dbFields;}

    static void create(LogLevel level, const std::string& source, const std::string& message);

    static QueryBuilder* query() {
        return newQueryBuilder();
    };
};



#endif //LOGMESSAGE_H
