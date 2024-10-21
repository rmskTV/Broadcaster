//
// Created by Руслан Москвитин on 30.09.2024.
//

#include "BaseModel.h"
#include "../Models/LogMessage.h"
#include <iostream>

std::vector<dbField> BaseModel::timeStampFields = {
    dbField(createdAtField, FIELD_TYPE::TIMESTAMP, "NULL",false),
    dbField(updatedAtField, FIELD_TYPE::TIMESTAMP, "NULL",false),
    dbField(deletedAtField, FIELD_TYPE::TIMESTAMP, "NULL",true),
};

