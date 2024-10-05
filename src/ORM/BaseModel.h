//
// Created by Руслан Москвитин on 30.09.2024.
//

#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <string>

#include <stdlib.h>
#include <iostream>
#include "DbConnection.h"

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
    /// @brief хеллоВорлд метод
    static void testSQL();
};



#endif //BASEMODEL_H
