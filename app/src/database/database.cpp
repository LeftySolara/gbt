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

#include <QFile>

#include "gbt/database.h"
#include "gbt/log.h"

Database::Database(const QString db_path)
{
    // Check whether the default connection already exists.
    if (QSqlDatabase::contains()) {
        return;
    }

    // The QSQLITE driver automatically creates the database file if it does not exist.
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_path);

    if (!db.open()) {
        qCCritical(LOG_GBT) << "ERROR: Unable to open application database";
    }
}

Database::~Database()
{
    close();
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
 * @brief Checks whether the database connection is open.
 * @return true if the database is open, false otherwise
 */
bool Database::isOpen()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.isOpen();
}
