//
// Created by Руслан Москвитин on 13.10.2024.
//

#ifndef DBFIELD_H
#define DBFIELD_H


/// @brief ENUM с разрешенными типами филдов в таблицах БД
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
enum class FIELD_TYPE {STRING, INTEGER, TEXT, DATETIME, TIMESTAMP};

/// @brief Возвращает название типа филда для использования в конструкторах SQL-запросов
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
inline const char* sqlFieldTypeNameFor(const FIELD_TYPE type)
{
    switch(type)
    {
        case FIELD_TYPE::STRING:       return "VARCHAR(255)";
        case FIELD_TYPE::INTEGER:      return "INTEGER";
        case FIELD_TYPE::DATETIME:     return "DATETIME";
        case FIELD_TYPE::TIMESTAMP:    return "TIMESTAMP";
        default:                       return "VARCHAR(255)";
    }
}

/// @brief Класс для описания конкретного поля в базе данных.
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
class  dbField {
    std::string name;
    FIELD_TYPE type;
    std::string defaultValue;
    bool is_nullable;

public:
    dbField(std::string name, const FIELD_TYPE type, std::string defaultValue, const bool is_nullable) {
        this->name = std::move(name);
        this->type = type;
        this->defaultValue = std::move(defaultValue);
        this->is_nullable = is_nullable;
    }


    [[nodiscard]] const std::string& getDefaultValue() const {
        return this->defaultValue;
    }

    [[nodiscard]] const std::string& getName() const {
        return this->name;
    }

     [[nodiscard]] bool getNullable() const {
        return this->is_nullable;
    }
    [[nodiscard]] FIELD_TYPE getType() const {
        return this->type;
    }
};
#endif //DBFIELD_H
