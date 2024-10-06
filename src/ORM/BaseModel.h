//
// Created by Руслан Москвитин on 30.09.2024.
//

#ifndef BASEMODEL_H
#define BASEMODEL_H
#pragma once
#include <string>
#include <utility>

/// @brief ENUM с разрешенными типами филдов в таблицах БД
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
enum class FIELD_TYPE {STRING, INTEGER};

/// @brief Класс для описания конкретного поля в базе данных.
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
class  dbField {
    std::string name;
    FIELD_TYPE type;
    std::string defaultValueString;
    int defaultValueInt;

public:
    dbField(std::string name, FIELD_TYPE type, std::string defaultValue) {
        this->name = std::move(name);
        this->type = type;
        this->defaultValueString = std::move(defaultValue);
        this->defaultValueInt = 0;
    }

    dbField(std::string name, FIELD_TYPE type, const int defaultValue) {
        this->name = std::move(name);
        this->type = type;
        this->defaultValueString = "";
        this->defaultValueInt = defaultValue;
    }
};

/// @brief Класс Базовой модели. Инкапсулирует взаимодействие С Базой данных для моделей приложения.
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
class BaseModel {

protected:

    /// @brief Название поля с Primary key индексом
    static inline std::string primaryKey = "id";

    /// @brief Тип поля с Primary key индексом
    static inline FIELD_TYPE primaryKeyType = FIELD_TYPE::INTEGER;

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
    static void checkTableFor(std::string *tableName, std::vector<dbField> *dbFields);

};



#endif //BASEMODEL_H
