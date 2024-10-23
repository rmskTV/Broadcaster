//
// Created by Руслан Москвитин on 05.10.2024.
//
#include "AppDispatcher.h"
#include "Models/LogMessage.h"
#include "Models/Channel.h"
#include "ORM/DbConnection.h"
#include "ORM/QueryBuilder.h"

void AppDispatcher::init() {
    setDbDefaultCredentialsForDbConnection();
    checkDbStructure();
}

void AppDispatcher::setDbDefaultCredentialsForDbConnection() {
    LogMessage::create(LogLevel::INFO, "AppDispatcher", "Устанавливаю параметры подключения к серверу БД по умолчанию");
    DbConnection::setDbAddress("tcp://127.0.0.1:3306");
    DbConnection::setDbUserName("root");
    DbConnection::setDbPassword("password");
    DbConnection::setDbBaseName("Broadcaster_base"); //"broadcaster_base"
}

void AppDispatcher::checkDbStructure() {
    LogMessage::create(LogLevel::INFO, "AppDispatcher", "Проверяю структуру БД");
    QueryBuilder::query()->createDataBase(DbConnection::getDbBaseName());
    DbConnection::useTargetDataBase();
    if (DbConnection::getConnection()) {
        LogMessage::query()->checkTable();
        Channel::query()->checkTable();
    }
}
