/******************************************************************************
 * gametablemodel.cpp : Editable data model for the game table
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

#include <QSqlQuery>
#include "gametablemodel.h"

/**
 * @brief Creates a new GameTableModel object.
 */
GameTableModel::GameTableModel(QObject *parent, QSqlDatabase db) : QSqlRelationalTableModel(parent)
{
}

/**
 * @brief Returns the data stored under the given role at index.
 * @param index The index of the data being requested.
 * @param role The role of the data being requested.
 * @return The data being requested. If there is no data, returns an empty QVariant.
 */
QVariant GameTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    return QSqlRelationalTableModel::data(index, role);
}

/**
 * @brief Returns the data for the given role and section in the header with the specified orientation.
 * @param section The data's section in the header.
 * @param orientation The orientation of the header (horizontal or vertical).
 * @param role The role of the data.
 * @return The data for the given role and header section.
 */
QVariant GameTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QSqlRelationalTableModel::headerData(section, orientation, role);
}

/**
 * @brief Adds a new game to the database.
 * @param title The title of the game.
 * @return true if game is added successfully, false otherwise.
 */
bool GameTableModel::addGame(const QString title) const
{
    if (gameExists(title)) {
        return false;
    }

    QSqlQuery query(database());
    const QString query_str = QString("INSERT INTO game (title) VALUES ('%1')").arg(title);
    return query.exec(query_str);
}

/**
 * @brief Determines if a game exists in the database.
 * @param title The title of the game.
 * @return true if the game is in the database, false otherwise.
 */
bool GameTableModel::gameExists(const QString title) const
{
    return getGameID(title) >= 0;
}

/**
 * @brief Gets the ID of a game in the database.
 * @param title The title of the game.
 * @return The ID of the game in the database, or -1 if the game is not in the database.
 */
int GameTableModel::getGameID(const QString title) const
{
    QSqlQuery query(database());
    const QString query_str = QString("SELECT id FROM game WHERE name = '%1'").arg(title);
    query.exec(query_str);

    if (query.next()) {
        const int id = query.value(0).toInt();
        const int max_id = getNextGameID();

        if (id >= max_id) {  // The game doesn't exist in the library.
            return -1;
        }
        else {
            return id;
        }
    }
    return -1;
}

/**
 * @brief Gets the next ID number that will be assigned when a game is added to the database.
 */
int GameTableModel::getNextGameID() const
{
    QSqlQuery query(database());
    query.exec("SELECT * FROM SQLITE_SEQUENCE WHERE name = 'game'");

    if (query.next()) {
        return query.value(1).toInt() + 1;
    }
    else {
        return -1;
    }
}
