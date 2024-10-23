//
// Created by Руслан Москвитин on 05.10.2024.
//

#include "DbConnection.h"
#include "../Models/LogMessage.h"
#include <utility>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <sys/stat.h>

sql::Connection *DbConnection::getConnection() {

    if (connection_ == nullptr) {
        try
        {
            LogMessage::create(LogLevel::INFO, "DbConnection", "Пробую установить новое подключение к БД");
            driver_ = get_driver_instance();
            connection_ = driver_->connect(db_address_, db_username_, db_password_);
            connection_->setSchema(db_name_);

        }
        catch (sql::SQLException e)
        {
            LogMessage::create(LogLevel::ERROR, "DbConnection", "Не удалось подключиться к серверу БД. Получена ошибка: " + std::string(e.what()));
            return nullptr;
        }
        LogMessage::create(LogLevel::INFO, "DbConnection", "Коннекшен установлен");
    }
    return connection_;
}

void DbConnection::closeConnection() {
    if (connection_ != nullptr) {
        LogMessage::create(LogLevel::INFO, "DbConnection", "Разрываю существующий коннекшен к БД");
        try
        {
            connection_->close();
            delete connection_;
        }
        catch (sql::SQLException e)
        {
            LogMessage::create(LogLevel::ERROR, "DbConnection", "Не удалось разорвать SQL-соединение. Получена ошибка: " + std::string(e.what()));
        }
        connection_ = nullptr;
    }
}

void DbConnection::setDbAddress(std::string db_address) {
    db_address_ = std::move(db_address);
    closeConnection();
}

void DbConnection::setDbUserName(std::string db_username) {
    db_username_ = std::move(db_username);
    closeConnection();
}

void DbConnection::setDbPassword(std::string db_password) {
    db_password_ = std::move(db_password);
    closeConnection();
}

void DbConnection::setDbBaseName(std::string db_name) {
    db_name_ = std::move(db_name);
    closeConnection();
}

void DbConnection::useTargetDataBase() {
    if (connection_ != nullptr) {
        try
        {
            getConnection()->setSchema(db_name_);
            LogMessage::create(LogLevel::INFO, "DbConnection", "Коннекшену назначена база " + getDbBaseName());
        }
        catch (sql::SQLException e)
        {
            LogMessage::create(LogLevel::ERROR, "DbConnection", "Не удалось назначить коннекшену базу. Получена ошибка: " + std::string(e.what()));
        }
    }
}

const std::string &DbConnection::getDbBaseName() {
    return db_name_;
}
