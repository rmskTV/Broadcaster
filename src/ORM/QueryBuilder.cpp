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
        _db_name = DbConnection::getDbBaseName();
    }
};
QueryBuilder::~QueryBuilder() {
    delete _statement;
    delete _result;
};

QueryBuilder *QueryBuilder::query() {
    return new QueryBuilder();
}
void QueryBuilder::createDataBase(const std::string& db_name) const {
    this->executeSqlStatement("CREATE DATABASE IF NOT EXISTS " + db_name);
}

void QueryBuilder::createTable(const std::string& tableName, dbField* dbField) const {
    this->executeSqlStatement("CREATE TABLE  IF NOT EXISTS "+ tableName +" ("+ dbField->getName() + " " +  sqlFIeldTypeNameFor(dbField->getType()) +" AUTO_INCREMENT PRIMARY KEY);");
}


bool QueryBuilder::columnExist(const std::string& tableName, const std::string& fieldName) {
    this->executeSqlQuery("SELECT COLUMN_NAME FROM information_schema.columns WHERE table_schema='"+_db_name+"' AND table_name='"+tableName+"' and column_name='"+fieldName+"';");
    while (_result->next()) {
        delete this;
        return true;
    }
    delete this;
    return false;
}

void QueryBuilder::createColumn(const std::string& tableName, dbField* field) {
    if (!this->columnExist(tableName, field->getName())) {
        LogMessage::create(LogLevel::WARNING, "QueryBuilder", field->getName() + " в " + tableName + " не существует. Добавляю.");
        query()->executeSqlStatement("ALTER TABLE " + tableName + " ADD " + field->getName() + " " + sqlFIeldTypeNameFor(field->getType()) + " DEFAULT '" + field->getDefaultValue()+ "';");
    }
}

void QueryBuilder::executeSqlQuery(const std::string& query) {
    try
    {
        if ( _statement != nullptr ) {
            _result = _statement->executeQuery(query);
        }
    }
    catch (sql::SQLException e)
    {
        LogMessage::create(LogLevel::ERROR, "QueryBuilder", "Не удалось выполнить запрос " +  query + ". Получена ошибка: " + std::string(e.what()));
    }
}
void QueryBuilder::executeSqlStatement(const std::string& query) const {
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