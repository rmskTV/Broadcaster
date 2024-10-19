//
// Created by Руслан Москвитин on 06.10.2024.
//

#include "LogMessage.h"
#include <wx/wx.h>
std::vector<dbField> LogMessage::dbFields = {
    dbField("_level", FIELD_TYPE::INTEGER, "0"),
    dbField("_source", FIELD_TYPE::STRING, ""),
    dbField("_message", FIELD_TYPE::STRING, ""),
};

void LogMessage::create(LogLevel level, const std::string& source, const std::string& message) {
    std::cout << std::to_string(static_cast<int>(level)) + " << " + source + " : " +  message << std::endl;
}