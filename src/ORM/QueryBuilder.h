//
// Created by Руслан Москвитин on 13.10.2024.
//

#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include "mysql_connection.h"
#include "DbField.h"
#include <cppconn/resultset.h>

/// @brief Класс QueryBuilder для построения запросов к Базе Данных через DbConnection
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
class QueryBuilder {

    ///@brief Указатель на sql::Statement выделенный в рамках инстанса
    sql::Statement* _statement = nullptr;

    ///@brief Указатель на ResultSet содержащий результат выполнения _statement
    sql::ResultSet* _result = nullptr;

    ///@brief Название БД, к которой строятся запросы
    static inline  std::string _db_name;

    ///@brief Выполняет собранный SQL-statement (Без возвращения результата выполнения)
    ///@param query SQL-команда
    void executeSqlStatement(const std::string& query) const;

    ///@brief Выполняет собранный SQL-query (Результат выполнения будет доступен в _result )
    ///@param query SQL-команда
    void executeSqlQuery(const std::string& query);

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

    ///@brief Метод, который проверяет наличие столбца в таблице
    /// @param tableName Название создаваемой таблицы
    /// @param fieldName Описание поля для Primary Key
    bool columnExist(const std::string& tableName, const std::string& fieldName);

    ///@brief Метод, который создаст в таблице нужный столбец (если его нет)
    /// @param tableName Название создаваемой таблицы
    /// @param field Требуемый столбец в виде экземпляра dbField
    void createColumn(const std::string& tableName, dbField* field);
};



#endif //QUERYBUILDER_H
