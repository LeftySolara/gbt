/******************************************************************************
 * dbutils.h : helper functions for database handling
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

#ifndef DBUTILS_H
#define DBUTILS_H

#include <QSqlDatabase>
#include <QStringList>

namespace DBUtils {

enum Column {
    ID,
    NAME,
    STATUS,
    SERIES,
    PLATFORM,
    GENRE,
    ART_PATH
};

static QStringList column_names = {
    "id",
    "name",
    "status_id",
    "series_id",
    "platform_id",
    "genre_id",
    "art_path"
};

static QStringList column_headers = {
    "ID",
    "Title",
    "Status",
    "Series",
    "Platform",
    "Genre",
    "Box Art"
};

static QStringList table_names = {
    "games",
    "status",
    "series",
    "platforms",
    "genres"
};

bool databaseFileExists();

bool createDatabaseFile();
bool createDatabaseSchema();
QSqlDatabase initializeDatabaseConnection();

bool executeSqlScript(QString script_path);
}

#endif // DBUTILS_H
