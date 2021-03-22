/******************************************************************************
 * database.cpp : Functions for managing the application database
 * ****************************************************************************
 * Copyright (C) 2021 Jalen Adams
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

#include <QDir>
#include <QSqlError>
#include <QSqlQuery>

#include "gbt/database.h"
#include "gbt/log.h"

void Database::open(const QString db_path)
{
    // If the default connection already exists, remove it
    // to allow for updating the file path if necessary.
    if (QSqlDatabase::contains()) {
        QSqlDatabase db = QSqlDatabase::database();
        connection_name = db.connectionName();
        close();
    }
    QSqlDatabase::removeDatabase(connection_name);

    // If the database file doesn't exist, we'll need to initialize the schema.
    QFile db_file(db_path);
    bool first_run = !db_file.exists();

    // The QSQLITE driver automatically creates the database file if it does not exist.
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    connection_name = db.connectionName();
    db.setDatabaseName(db_path);

    if (!db.open()) {
        qCCritical(LOG_GBT) << "ERROR: Unable to open application database";
    }
    if (first_run) {
        run_migration(migration_prefix + "/000");
        update_schema(-1);
    }
}

/**
 * @brief Closes the active database connection.
 */
void Database::close()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
}

/**
 * @brief Runs a migration on the current database connection.
 * @param script_path Path to the SQL script containing migration commands.
 * @return true if the migration runs successfully, false otherwise
 */
bool Database::run_migration(const QString &script_path)
{
    QFile script(script_path);
    if (!script.open(QIODevice::ReadOnly)) {
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.transaction()) {
        return false;
    }

    QString line;
    QString sql_statement = "";
    QTextStream stream(&script);
    QSqlQuery query;

    while (!stream.atEnd()) {
        line = stream.readLine();
        if (line.startsWith("--") || line.length() == 0) { // ignore comments and blank lines
            continue;
        }
        sql_statement += line;
        if (sql_statement.endsWith(";")) {
            sql_statement.chop(1); // remove trailing semicolon
            if (query.prepare(sql_statement)) {
                query.exec();
                sql_statement = "";
            } else {
                return false;
            }
        }
    }

    // Make sure the query is inactive because otherwise the commit may fail.
    if (query.isActive()) {
        query.finish();
    }
    if (!db.commit()) {
        db.rollback();
    }
    script.close();
    return true;
}

/**
 * @brief Updates the database schema to the spedified version.
 * @param version The version to update the database schema to, or -1 for the latest.
 */
void Database::update_schema(const int &version)
{
    int current_schema_version = schemaVersion();
    if (version >= 0 && current_schema_version > version) {
        return;
    }

    QStringList migrations =
            QDir(migration_prefix).entryList(QDir::NoFilter, QDir::Name | QDir::IgnoreCase);

    const int target_version = (version == -1) ? migrations.size() - 1 : version;
    bool success = true;

    for (int i = current_schema_version + 1; i <= target_version; ++i) {
        if (!run_migration(":/migrations/" + migrations[i])) {
            qCritical(LOG_GBT) << "Unable to run migration.";
            success = false;
            break;
        }
    }

    if (!success) {
        QSqlDatabase db = QSqlDatabase::database();
        qCCritical(LOG_GBT) << db.lastError().text();
    }
}

/**
 * @brief Checks whether the database connection is open.
 * @return true if the database is open, false otherwise
 */
bool Database::isOpen()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.isOpen();
}

/**
 * @brief Gets the current version of the database schema.
 * @return The schema version number.
 */
unsigned int Database::schemaVersion()
{
    QSqlQuery query("PRAGMA user_version");
    query.next();
    QVariant user_version = query.value(0);
    return user_version.toUInt();
}
