//
// Created by Руслан Москвитин on 13.10.2024.
//

#ifndef DBFIELD_H
#define DBFIELD_H


/// @brief ENUM с разрешенными типами филдов в таблицах БД
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
enum class FIELD_TYPE {STRING, INTEGER};

/// @brief Возвращает название типа филда для использования в конструкторах SQL-запросов
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
inline const char* sqlFIeldTypeNameFor(FIELD_TYPE type)
{
    switch(type)
    {
        case FIELD_TYPE::STRING:       return "VARCHAR(255)";
        case FIELD_TYPE::INTEGER:      return "INTEGER";
    }
    return "VARCHAR[255]";
}

/// @brief Класс для описания конкретного поля в базе данных.
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
class  dbField {
    std::string name;
    FIELD_TYPE type;
    std::string defaultValue;

public:
    dbField(std::string name, const FIELD_TYPE type, std::string defaultValue) {
        this->name = std::move(name);
        this->type = type;
        this->defaultValue = std::move(defaultValue);
    }


    std::string getDefaultValue() {
        return this->defaultValue;
    }

    std::string getName() {
        return this->name;
    }
    [[nodiscard]] FIELD_TYPE getType() const {
        return this->type;
    }
};
#endif //DBFIELD_H
