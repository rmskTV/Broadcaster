//
// Created by Руслан Москвитин on 06.10.2024.
//

#include "LogMessage.h"
#include <wx/wx.h>
std::vector<dbField> LogMessage::dbFields = {
    dbField("_level", FIELD_TYPE::INTEGER, "0", false),
    dbField("_source", FIELD_TYPE::STRING, "", false),
    dbField("_message", FIELD_TYPE::TEXT, "", false),
};

void LogMessage::create(LogLevel level, const std::string& source, const std::string& message) {
    // LogMessage::query()->insert<LogMessage>(
    //     std::vector<dbField>  {
    //         dbField("_level", FIELD_TYPE::INTEGER, indexForLevel(level)),
    //         dbField("_source", FIELD_TYPE::STRING, source),
    //         dbField("_message", FIELD_TYPE::TEXT, message),
    //     }
    // );
    std::cout << std::to_string(static_cast<int>(level)) + " << " + source + " : " +  message << std::endl;
}