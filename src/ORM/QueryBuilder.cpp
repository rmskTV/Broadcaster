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
    this->executeSql("CREATE DATABASE IF NOT EXISTS " + db_name);
}

void QueryBuilder::createTable(const std::string& tableName, dbField* dbField) const {
    this->executeSql("CREATE TABLE  IF NOT EXISTS "+ tableName +" ("+ dbField->getName() + " " +  sqlFIeldTypeNameFor(dbField->getType()) +" AUTO_INCREMENT PRIMARY KEY);");
}


void QueryBuilder::executeSql(const std::string& query) const {
    try
    {
        if ( _statement != nullptr ) {
            _statement->execute(query);
        }
    }
    catch (sql::SQLException e)
    {
        LogMessage::create(LogLevel::ERROR, "QueryBuilder", "Не удалось выполнить запрос " +  query + ". Получена ошибка: " + std::string(e.what()));
    }

    delete this;
}

