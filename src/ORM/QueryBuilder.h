//
// Created by Руслан Москвитин on 13.10.2024.
//

#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include "mysql_connection.h"
#include "DbField.h"

/// @brief Класс QueryBuilder для построения запросов к Базе Данных через DbConnection
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
class QueryBuilder {
    ///@brief Указатель на sql::Statement выделенный в рамках инстанса
    sql::Statement* _statement = nullptr;
    ///@brief Выполняет собранную SQL-команда
    ///@param query SQL-команда
    void executeSql(const std::string& query) const;
    QueryBuilder();
    ~QueryBuilder();
public:
    ///@brief Инстанцирует экземпляр класса
    static QueryBuilder* query();

    ///@brief Метод, который создает Базу данных (если базы не существует)
    /// @param db_name Название создаваемой базы
    void createDataBase(const std::string& db_name) const;

    ///@brief Метод, который создает Таблицу (если ее не существует)
    /// @param tableName Название создаваемой таблицы
    /// @param dbField Описание поля для Primary Key
    void createTable(const std::string& tableName, dbField* dbField) const;

};



#endif //QUERYBUILDER_H
