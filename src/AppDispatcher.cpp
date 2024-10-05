//
// Created by Руслан Москвитин on 05.10.2024.
//

#include "AppDispatcher.h"
void AppDispatcher::init() {
    setDbDefaultCredentialsForDbConnection();
    checkDbStructure();
}

void AppDispatcher::setDbDefaultCredentialsForDbConnection() {
    DbConnection::setDbAddress("tcp://127.0.0.1:3306");
    DbConnection::setDbUserName("root");
    DbConnection::setDbPassword("password");
    DbConnection::setDbBaseName("Broadcaster_base"); //"broadcaster_base"
}

void AppDispatcher::checkDbStructure() {
    sql::Statement* stmt = DbConnection::getConnection()->createStatement();
    stmt->execute((std::string)"CREATE DATABASE IF NOT EXISTS " + (std::string)DbConnection::getDbBaseName());
    std::cout << "Check DB " + (std::string)DbConnection::getDbBaseName() << std::endl;
    delete stmt;
    DbConnection::useTargetDataBase();
}
