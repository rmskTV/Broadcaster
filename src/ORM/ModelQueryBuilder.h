//
// Created by Руслан Москвитин on 21.10.2024.
//

#ifndef MODELQUERYBUILDER_H
#define MODELQUERYBUILDER_H
#include "QueryBuilder.h"
#include <cstdlib>

/// @brief Класс ModelQueryBuilder для построения запросов к Базе Данных с привязкой к модели
/// @authors Ruslan Moskvitin
/// @date Октябрь 2024
template<typename T>
class ModelQueryBuilder {

    public:
    ModelQueryBuilder() = delete;
    ~ModelQueryBuilder() = delete;

    ///@brief Инстанцирует экземпляр класса QueryBuilder
    static QueryBuilder* query() {
        return QueryBuilder::query()
        ->setTableName(T::getTableName())
        ->setPrimaryKeyField(T::getPrimaryKeyField())
        ->setTimeStampsFields(T::getTimeStampsFields())
        ->setFields(T::getDbFields());
    };

};



#endif //MODELQUERYBUILDER_H
