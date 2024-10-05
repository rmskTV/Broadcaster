//
// Created by Руслан Москвитин on 05.10.2024.
//

#include "AppDispatcher.h"
void AppDispatcher::init() {
    setDbDefaultCredentials();
}

void AppDispatcher::setDbDefaultCredentials() {
    DbConnection::setDbAddress("tcp://127.0.0.1:3306");
    DbConnection::setDbUserName("root");
    DbConnection::setDbPassword("password");
}

