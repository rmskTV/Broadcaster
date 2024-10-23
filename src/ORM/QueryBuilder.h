//
// Created by Руслан Москвитин on 13.10.2024.
//

#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include "mysql_connection.h"
#include "DbField.h"
#include "BaseModel.h"
#include <cppconn/resultset.h>
#include <cstdlib>
#include <vector>
/// @brief Класс QueryBuilder для построения запросов к Базе Данных через DbConnection
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
class QueryBuilder {

    ///@brief Указатель на sql::Statement выделенный в рамках инстанса
    sql::Statement* _statement = nullptr;

    ///@brief Указатель на ResultSet содержащий результат выполнения _statement
    sql::ResultSet* _result = nullptr;

    ///@brief Название БД, к которой строятся запросы
    static inline  std::string _dbName;

    ///@brief Название таблицы, к которой строятся запросы
    std::string _tableName;

    /// @brief Описание PK-поля таблицы к которой строятся запросы
    dbField* _primaryKeyField = nullptr;

    ///@brief  Список полей таблицы, к которой строятся запросы
    std::vector<dbField>* _dbFields = nullptr;

    ///@brief  Список TIMESTAMP-полей таблицы, к которой строятся запросы
    std::vector<dbField>* _timeStampsFields = nullptr;

    ///@brief Выполняет собранный SQL-statement (Без возвращения результата выполнения)
    ///@param query SQL-команда
    void executeSqlStatement(const std::string& query) const;

    ///@brief Выполняет собранный SQL-query (Результат выполнения будет доступен в _result )
    ///@param query SQL-команда
    void executeSqlQuery(const std::string& query);


    ///@brief Метод, который создает Таблицу (если ее не существует)
    void createTable() const;

    ///@brief Метод, который проверяет наличие столбца в таблице
    /// @param fieldName Описание поля для Primary Key
    bool columnExist(const std::string& fieldName);

    ///@brief Метод, который создаст в таблице нужный столбец (если его нет)
    /// @param field Требуемый столбец в виде экземпляра dbField
    void createColumn(const dbField* field);


    QueryBuilder();
    ~QueryBuilder();
public:
    ///@brief Инстанцирует экземпляр класса
    static QueryBuilder* query();

    ///@brief Метод, который привяжет запрос к определенной таблице
    /// @param tableName Название таблицы
    QueryBuilder* setTableName(const std::string& tableName) {
        _tableName = tableName;
        return this;
    };

    ///@brief Метод, который описывает PK таблицы, к которой делается запрос
    /// @param dbField Описание PK-поля
    QueryBuilder* setPrimaryKeyField(dbField* dbField) {
        _primaryKeyField = dbField;
        return this;
    };

    ///@brief Метод, который описывает TimeStamp-поля таблицы, к которой делается запрос
    /// @param dbFields поля таблицы
    QueryBuilder* setTimeStampsFields(std::vector<dbField>* dbFields) {
        _timeStampsFields = dbFields;
        return this;
    }

    ///@brief Метод, который описывает остальные поля таблицы, к которой делается запрос
    /// @param dbFields поля таблицы
    QueryBuilder* setFields(std::vector<dbField>* dbFields) {
        _dbFields = dbFields;
        return this;
    }

    ///@brief Метод, который создает Базу данных (если базы не существует)
    /// @param db_name Название создаваемой базы
    void createDataBase(const std::string& db_name) const;

    ///@brief Проверяет структуру таблицы
    void checkTable();

};



#endif //QUERYBUILDER_H
