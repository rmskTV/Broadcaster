//
// Created by Руслан Москвитин on 30.09.2024.
//

#include "BaseModel.h"
#include "../Models/LogMessage.h"
#include <stdlib.h>
#include <iostream>
#include <utility>
#include "DbConnection.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>


void BaseModel::checkTableFor(std::string* tableName, std::vector<dbField>* dbFields) {
    LogMessage::create(LogLevel::INFO, "BaseModel", "Проверяю структуру таблицы " + *tableName);

    sql::Connection* con = DbConnection::getConnection();
    sql::Statement* stmt;
    stmt = con->createStatement();
    stmt->execute("CREATE TABLE  IF NOT EXISTS "+ *tableName +" (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
    delete stmt;
}

void BaseModel::testSQL() {

    sql::Connection* con = DbConnection::getConnection();
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;

    stmt = con->createStatement();
    stmt->execute("DROP TABLE IF EXISTS inventory");
    std::cout << "Finished dropping table (if existed)" << std::endl;
    stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
    std::cout << "Finished creating table" << std::endl;
    delete stmt;

    pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)");
    pstmt->setString(1, "banana");
    pstmt->setInt(2, 150);
    pstmt->execute();
    std::cout << "One row inserted." << std::endl;

    pstmt->setString(1, "orange");
    pstmt->setInt(2, 154);
    pstmt->execute();
    std::cout << "One row inserted." << std::endl;

    pstmt->setString(1, "apple");
    pstmt->setInt(2, 100);
    pstmt->execute();
    std::cout << "One row inserted." << std::endl;

    delete pstmt;
    DbConnection::closeConnection();
}