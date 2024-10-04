//
// Created by Руслан Москвитин on 30.09.2024.
//

#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <string>

#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

/// @brief Класс Базовой модели. Инкапсулирует взаимодействие С Базой данных для моделей приложения.
/// @authors Ruslan Moskvitin
/// @date октябрь 2024
class BaseModel {

protected:
    /// @brief Название таблицы, ассоциированной с моделью
    std::string table;

    /// @brief Название поля с Primary key индексом
    std::string primaryKey = "id";

    /// @brief Тип поля с Primary key индексом
    std::string primaryKeyType = "int";

    /// @brief Поддержка автоинкремента PK-полем
    bool autoIncremented = true;

    /// @brief Неокончательное удаление экземпляров
    bool useSoftDeleting = true;

    /// @brief Количество экземпляров на страницу при пагинации
    int perPage = 15;

    /// @brief название поля для Created_at
    std::string createdAtField = "created_at";

    /// @brief название поля для Updated_at
    std::string updatedAtField = "updated_at";

    /// @brief название поля для Deleted_at
    std::string deletedAtField = "deleted_at";

public:
    static void testSQL() {

        const std::string server = "tcp://127.0.0.1:3306";
        const std::string username = "root";
        const std::string password = "password";

        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;

        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e)
        {
            std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
            system("pause");
            exit(1);
        }

        //please create database "quickstartdb" ahead of time
        con->setSchema("cpp_base");

        stmt = con->createStatement();
        stmt->execute("DROP TABLE IF EXISTS inventory");
        std::cout << "Finished dropping table (if existed)" << std::endl;
        stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
        std::cout << "Finished creating table" << std::endl;
        delete stmt;

        pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)");
        pstmt->setString(1, "banana");
        pstmt->setInt(2, 150);
        pstmt->execute();
        std::cout << "One row inserted." << std::endl;

        pstmt->setString(1, "orange");
        pstmt->setInt(2, 154);
        pstmt->execute();
        std::cout << "One row inserted." << std::endl;

        pstmt->setString(1, "apple");
        pstmt->setInt(2, 100);
        pstmt->execute();
        std::cout << "One row inserted." << std::endl;

        delete pstmt;
        delete con;
    }
};



#endif //BASEMODEL_H
