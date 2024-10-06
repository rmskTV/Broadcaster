//
// Created by Руслан Москвитин on 30.09.2024.
//

#include "Channel.h"


std::vector<dbField> Channel::dbFields = {
    dbField(primaryKey, primaryKeyType,0),
    dbField("_name", FIELD_TYPE::STRING, "")
};
