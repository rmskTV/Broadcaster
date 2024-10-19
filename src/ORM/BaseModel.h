//
// Created by Руслан Москвитин on 30.09.2024.
//

#ifndef BASEMODEL_H
#define BASEMODEL_H
#pragma once
#include <string>
#include <map>
#include <utility>
#include "DbField.h"


/// @brief Класс Базовой модели. Инкапсулирует взаимодействие С Базой данных для моделей приложения.
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
class BaseModel {

protected:
    /// @brief Название поля с Primary key индексом
    static inline std::string primaryKey = "id";

    /// @brief Тип поля с Primary key индексом
    static inline FIELD_TYPE primaryKeyType = FIELD_TYPE::INTEGER;

    static inline dbField primaryKeyField = dbField(primaryKey, primaryKeyType, "");
    /// @brief Неокончательное удаление экземпляров
    static inline bool useSoftDeleting = true;

    /// @brief Количество экземпляров на страницу при пагинации
    static inline int perPage = 15;

    /// @brief Название поля для Created_at
    static inline std::string createdAtField = "created_at";

    /// @brief Название поля для Updated_at
    static inline std::string updatedAtField = "updated_at";

    /// @brief Название поля для Deleted_at
    static inline std::string deletedAtField = "deleted_at";

public:
    virtual ~BaseModel() = default;

    /// @brief хеллоВорлд метод
    static void testSQL();
    ///@brief Проверяет структуру таблицы для переданного класса
    static void checkTableFor(const std::string *tableName, std::vector<dbField> *dbFields);

};



#endif //BASEMODEL_H
