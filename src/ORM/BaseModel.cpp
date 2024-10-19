//
// Created by Руслан Москвитин on 30.09.2024.
//

#include "BaseModel.h"
#include "../Models/LogMessage.h"
#include <iostream>
#include "QueryBuilder.h"


void BaseModel::checkTableFor(const std::string* tableName, std::vector<dbField>* dbFields) {
    LogMessage::create(LogLevel::INFO, "BaseModel", "Проверяю структуру таблицы " + *tableName);
    QueryBuilder::query()->createTable(*tableName, &primaryKeyField);
    for (dbField& field : *dbFields) {
        QueryBuilder::query()->createColumn(*tableName, &field);
    }
}
