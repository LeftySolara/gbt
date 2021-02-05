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

const QString Database::db_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
                                    + "/gbt/gbt.sqlite3";

Database::Database()
{
    if (!exists()) {
        qCInfo(LOG_GBT) << "No application database found. Creating...";

        QFile db_file(db_path);
        db_file.open(QIODevice::ReadWrite);
        db_file.close();

        // TODO: run SQL script to set up schema
        qCInfo(LOG_GBT) << "Database created successfully.";
    }
}

/**
 * @brief Checks whether the database exists.
 * @return true if the database exists, false otherwise.
 */
bool Database::exists()
{
    QFile db_file(db_path);
    return db_file.exists();
}
