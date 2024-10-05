//
// Created by Руслан Москвитин on 05.10.2024.
//

#include "DbConnection.h"

#include <utility>

sql::Connection *DbConnection::openConnection() {

    if (connection_ == nullptr) {
        try
        {
            std::cout << " Пробую запустить новый коннекшн " << std::endl;
            driver_ = get_driver_instance();
            connection_ = driver_->connect(db_address_, db_username_, db_password_);
        }
        catch (sql::SQLException e)
        {
            std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
            return nullptr;
        }
    }
    else {
        std::cout << " Коннекшн существует " << std::endl;
    }
    return connection_;
}

void DbConnection::closeConnection() {
    if (connection_ != nullptr) {
        connection_->close();
        delete connection_;
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
