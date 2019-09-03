/******************************************************************************
 * dbutils.cpp : helper functions for database handling
 * ****************************************************************************
 * Copyright (C) 2019 Jalen Adams
 *
 * Authors: Jalen Adams <jalen@jalenkadams.me>
 *
 * This file is part of gbt.
 *
 * gbt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gbt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gbt.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "dbutils.h"
#include "settings/settings.h"

#include <QFile>
#include <QSqlQuery>
#include <QTextStream>

bool DBUtils::databaseFileExists()
{
    QFile database_file(Settings::getDatabasePath());
    return database_file.exists();
}

bool DBUtils::createDatabaseFile()
{
    QFile database_file(Settings::getDatabasePath());
    database_file.open(QIODevice::ReadWrite);
    database_file.close();

    return database_file.exists();
}

bool DBUtils::createDatabaseSchema()
{
    // If a debug build is running, populate the database with sample data.
    QString init_script_path;
    #ifdef QT_DEBUG
        init_script_path = "../../gbt/scripts/init_db_sample_data.sql";
    #else
        init_script_path = "../../gbt/scripts/init_db.sql";
    #endif

    if (executeSqlScript(init_script_path))
        qInfo("Successfully created and initialized database.");
    else {
        qCritical("Error: failed to create database.");
        return false;
    }

    return true;
}

QSqlDatabase DBUtils::initializeDatabaseConnection()
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(Settings::getDatabasePath());

    return database;
}

bool DBUtils::executeSqlScript(QString script_path)
{
    QFile script(script_path);
    if (!script.open(QIODevice::ReadOnly))
        return false;

    QString line;
    QString sql_statement = "";
    QTextStream stream(&script);
    QSqlQuery query;

    while (!stream.atEnd()) {
        line = stream.readLine();
        if (line.startsWith("--") || line.length() == 0) // ignore comments
            continue;

        sql_statement += line;
        if (sql_statement.endsWith(";")) {
            sql_statement.chop(1);  // remove trailing semicolon
            if (query.prepare(sql_statement)) {
                query.exec();
                sql_statement = "";
            }
            else
                return false;
        }
    }
    script.close();
    return true;
}

