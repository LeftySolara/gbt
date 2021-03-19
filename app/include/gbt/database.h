/******************************************************************************
 * database.h : Functions for managing the application database
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

#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QStandardPaths>

namespace Database
{
    namespace
    {
        QString connection_name;

        static const QString migration_prefix = ":/migrations";
        static const QString default_db_path =
                QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/gbt/gbt.sqlite3";
    }

    void open(const QString db_path = default_db_path);
    void close();

    bool run_migration(const QString &script_path);
    void update_schema(const int &version = -1);

    bool isOpen();
    unsigned int schemaVersion();
}

#endif // DATABASE_H
