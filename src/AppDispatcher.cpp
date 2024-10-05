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
    DbConnection::setDbBaseName("cpp_base"); //"broadcaster_base"
}

void AppDispatcher::checkDbStructure() {

}
