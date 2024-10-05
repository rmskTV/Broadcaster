//
// Created by Руслан Москвитин on 05.10.2024.
//

#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <sys/stat.h>

#include "../AppDispatcher.h"


/// @brief Класс DbConnection для настройки коннекшена к Базе Данных через cppconnection
/// @authors Ruslan Moskvitin
/// @date октябрь 2024
class DbConnection {
    ///@brief Указатель на непосредственно экземпляр sql::Connection
    static inline sql::Connection* connection_;

    ///@brief Указатель на непосредственно экземпляр sql::Driver
    static inline sql::Driver* driver_;

    ///@brief Адрес сервера с БД
    static inline std::string db_address_;

    ///@brief Логин пользователя для доступа к серверу БД
    static inline std::string db_username_;

    ///@brief Пароль пользователя для доступа к серверу БД
    static inline std::string db_password_;

    ///@brief Название БД
    static inline std::string db_name_;

public:
    ///@brief Устанавливает коннекшену Адрес БД
    ///@param db_address Адрес сервера. Например, tcp://127.0.0.1:3306
    static void setDbAddress(std::string db_address);

    ///@brief Устанавливает коннекшену имя пользователя
    ///@param db_username Имя пользвателя. Например, root
    static void setDbUserName(std::string db_username);

    ///@brief Устанавливает коннекшену пароль пользователя
    ///@param db_password Пароль пользвателя. Например, 1234321
    static void setDbPassword(std::string db_password);

    ///@brief Устанавливает название базы, с которой нужно работать в рамках коннекшена
    ///@param db_name Название базы. Например, BroadcaterBase
    static void setDbBaseName(std::string db_name);

    ///@brief Открывает соединение (коннекшен) к серверу БД и возвращает указатель на него. В случае ошибки возвращает nullptr
    static sql::Connection* openConnection();

    ///@brief Закрывает и удаляет существующий коннекшн с БД.
    static void closeConnection();


};



#endif //DBCONNECTION_H
