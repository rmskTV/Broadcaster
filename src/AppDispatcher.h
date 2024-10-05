//
// Created by Руслан Москвитин on 05.10.2024.
//

#ifndef APPDISPATCHER_H
#define APPDISPATCHER_H

#include "ORM/DbConnection.h"


class AppDispatcher {
    ///@brief Устанавливает логин/пароль и адрес БД по умолчанию
    static void setDbDefaultCredentials();
public:

    static void init();

};



#endif //APPDISPATCHER_H
