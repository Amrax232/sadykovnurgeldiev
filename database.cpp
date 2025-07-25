 #pragma once
#include "database.h"
#include <QCoreApplication>
#include <QVariant>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>


Database::Database()
{
    initDB();
}

void Database::initDB() {
    this->dbInstance = QSqlDatabase::addDatabase("QSQLITE");
    this->dbInstance.setDatabaseName("db2.sql");
    if (!this->dbInstance.open()) {
        qDebug() << this->dbInstance.lastError().text();
    }
    this->doSQLQuery("CREATE TABLE IF NOT EXISTS Users (userID INTEGER PRIMARY KEY, login VARCHAR (255) UNIQUE NOT NULL, password VARCHAR (255) NOT NULL, token VARCHAR (255) UNIQUE NOT NULL, isTeacher BOOL NOT NULL)");
    this->doSQLQuery("CREATE TABLE IF NOT EXISTS Tasks (taskID INTEGER PRIMARY KEY, text VARCHAR (1024) NOT NULL, answer VARCHAR (1024) NOT NULL, type INT NOT NULL)");
    this->doSQLQuery("CREATE TABLE IF NOT EXISTS UsersTasks (userID int references Users(userID), taskID int references Tasks(taskID), primary key (userID, taskID))");
    this->doSQLQuery("INSERT INTO Users (userID, login, password, token, isTeacher) VALUES (1, 'admin', 'admin', 'admin_token', 1) ON CONFLICT (userID) DO NOTHING;");

    // Добавление задач в таблицу Tasks
    this->doSQLQuery("INSERT INTO Tasks (taskID, text, answer, type) VALUES (1, 'Solve 2 + 2', '4', 1) ON CONFLICT (taskID) DO NOTHING;");
    this->doSQLQuery("INSERT INTO Tasks (taskID, text, answer, type) VALUES (2, 'What is 5 * 3?', '15', 1) ON CONFLICT (taskID) DO NOTHING;");
    this->doSQLQuery("INSERT INTO Tasks (taskID, text, answer, type) VALUES (3, 'Find x: x - 7 = 10', '17', 2) ON CONFLICT (taskID) DO NOTHING;");

    // Связывание задач с пользователем в таблице UsersTasks
    this->doSQLQuery("INSERT INTO UsersTasks (userID, taskID) VALUES (1, 1) ON CONFLICT (userID, taskID) DO NOTHING;");
    this->doSQLQuery("INSERT INTO UsersTasks (userID, taskID) VALUES (1, 2) ON CONFLICT (userID, taskID) DO NOTHING;");
    this->doSQLQuery("INSERT INTO UsersTasks (userID, taskID) VALUES (1, 3) ON CONFLICT (userID, taskID) DO NOTHING;");
};

Database::~Database() {
    this->dbInstance.close();
};

QSqlQuery Database::doSQLQuery(QString stringQuery) {
    QSqlQuery query(this->dbInstance);
    bool status = query.exec(stringQuery);
    qDebug().noquote() << QString("Query %1, status %2").arg(stringQuery).arg(status);
    if (!status) {
      this->dbInstance.rollback();
    }
    else {
        this->dbInstance.commit();
    }
    return query;
}

Database* Database::pInstance = nullptr;
QSqlDatabase Database::dbInstance;
DatabaseDestroyer Database::destroyer;
