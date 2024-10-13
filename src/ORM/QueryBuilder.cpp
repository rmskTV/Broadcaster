//
// Created by Руслан Москвитин on 13.10.2024.
//

#include "QueryBuilder.h"
#include "DbConnection.h"
#include "../Models/LogMessage.h"
#include <cppconn/statement.h>
#include <string>
QueryBuilder::QueryBuilder() {
    if (DbConnection::getConnection() == nullptr) {
        LogMessage::create(LogLevel::ERROR, "QueryBuilder", "DbConnection::getConnection() возвращает nullptr ");
    }
    else {
        _statement = DbConnection::getConnection()->createStatement();
    }
};
QueryBuilder::~QueryBuilder() {
    delete _statement;
};

QueryBuilder *QueryBuilder::query() {
    return new QueryBuilder();
}
void QueryBuilder::createDataBase(const std::string& db_name) const {
    try
    {
        if ( _statement != nullptr ) {
            _statement->execute(static_cast<std::string>("CREATE DATABASE IF NOT EXISTS ") + db_name);
        }
    }
    catch (sql::SQLException e)
    {
        LogMessage::create(LogLevel::ERROR, "QueryBuilder", "Не удалось создать базу " + db_name + ". Получена ошибка: " + std::string(e.what()));
    }

    delete this;
}

void QueryBuilder::createTable(const std::string& tableName, dbField* dbField) const {
    try
    {
        if ( _statement != nullptr ) {
            _statement->execute("CREATE TABLE  IF NOT EXISTS "+ tableName +" ("+ dbField->getName() + " " +  sqlFIeldTypeNameFor(dbField->getType()) +" AUTO_INCREMENT PRIMARY KEY);");
        }
    }
    catch (sql::SQLException e)
    {
        LogMessage::create(LogLevel::ERROR, "QueryBuilder", "Не удалось проверить таблицу " + tableName + ". Получена ошибка: " + std::string(e.what()));
    }

    delete this;
}

