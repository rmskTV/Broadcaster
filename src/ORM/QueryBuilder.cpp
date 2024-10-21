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
        _dbName = DbConnection::getDbBaseName();
        _statement = DbConnection::getConnection()->createStatement();
    }
};
QueryBuilder::~QueryBuilder() {
    delete _statement;
    delete _result;
};

QueryBuilder *QueryBuilder::query() {
    return new QueryBuilder();
}

//ПУБЛИЧНЫЕ МЕТОДЫ. ВЫПОЛНЕНИЕ КАЖДОГО ИЗ НИХ ДОЛЖНО ЗАКАНЧИВАТЬСЯ УДАЛЕНИЕМ ИНСТАНСА!

void QueryBuilder::checkTable() {
    LogMessage::create(LogLevel::INFO, "QueryBuilder", "Проверяю структуру таблицы " + _tableName);
    this->createTable();

    for (dbField& field : *_dbFields) {
        this->createColumn(&field);
    }

    for (dbField& field : *_timeStampsFields) {
        this->createColumn(&field);
    }

    delete this;
}

void QueryBuilder::createDataBase(const std::string& db_name) const {
    this->executeSqlStatement("CREATE DATABASE IF NOT EXISTS " + db_name);
    delete this;
}

// НИЖЕ ИДУТ ЧАСТНЫЕ МЕТОДЫ

void QueryBuilder::createTable() const {
    this->executeSqlStatement("CREATE TABLE  IF NOT EXISTS "+ _tableName +" ("+ _primaryKeyField->getName() + " " +  sqlFieldTypeNameFor(_primaryKeyField->getType()) +" AUTO_INCREMENT PRIMARY KEY);");
}


bool QueryBuilder::columnExist(const std::string& fieldName) {
    this->executeSqlQuery("SELECT COLUMN_NAME FROM information_schema.columns WHERE table_schema='"+_dbName+"' AND table_name='"+_tableName+"' and column_name='"+fieldName+"';");
    while (_result->next()) {
        return true;
    }
    return false;
}

void QueryBuilder::createColumn( const dbField* field) {
    if (!this->columnExist(field->getName())) {
        LogMessage::create(LogLevel::WARNING, "QueryBuilder", field->getName() + " в " + _tableName + " не существует. Добавляю.");
        if (field->getNullable()) {
            this->executeSqlStatement("ALTER TABLE " + _tableName + " ADD " + field->getName() + " " + sqlFieldTypeNameFor(field->getType()) + " DEFAULT NULL;");
        }
        else {
            if (field->getDefaultValue() == "NULL" || field->getDefaultValue().empty()) {
                this->executeSqlStatement("ALTER TABLE " + _tableName + " ADD " + field->getName() + " " + sqlFieldTypeNameFor(field->getType()) + " NOT NULL;");
            }
            else {
                this->executeSqlStatement("ALTER TABLE " + _tableName + " ADD " + field->getName() + " " + sqlFieldTypeNameFor(field->getType()) + " NOT NULL DEFAULT '" + field->getDefaultValue()+ "';");
            }
        }
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

}