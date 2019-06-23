/******************************************************************************
 * gamesdatabasemodel.cpp : data model for the games database
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

#include "gamesdatabasemodel.h"

#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextStream>
#include <QVector>
#include <QDebug>

GamesDatabaseModel::GamesDatabaseModel(QObject *parent, QSqlDatabase db)
    : QSqlRelationalTableModel(parent)
{
}

QVariant GamesDatabaseModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    return QSqlRelationalTableModel::data(index, role);
}

int GamesDatabaseModel::getGameID(QString title)
{
    QSqlQuery query(database());
    QString query_string = "SELECT id FROM games WHERE name = '" + title + "'";
    query.exec(query_string);

    if (query.next()) {
        int id = query.value(0).toInt();
        int next_id = getNextGameID();

        if (id >= next_id) // Game doesn't exist
            return -1;
        else
            return id;
    }

    return -1;
}

int GamesDatabaseModel::getSeriesID(QString series)
{
    QSqlQuery query(database());
    QString query_string = "SELECT * FROM series WHERE name = '" + series + "'";
    query.exec(query_string);

    if (query.next()) {
        int id = query.value(0).toInt();
        int next_id = getNextSeriesID();

        if (id >= next_id) // Series doesn't exist
            return -1;
        else
            return id;
    }

    return -1;
}

int GamesDatabaseModel::getPlatformID(QString platform)
{
    QSqlQuery query(database());
    QString query_string = "SELECT * FROM platforms WHERE name = '" + platform + "'";
    query.exec(query_string);

    if (query.next()) {
        int id = query.value(0).toInt();
        int next_id = getNextPlatformID();

        if (id >= next_id)  // Platform doesn't exist
            return -1;
        else
            return id;
    }

    return -1;
}

int GamesDatabaseModel::getNextGameID()
{
    QSqlQuery query(database());
    query.exec("SELECT * FROM SQLITE_SEQUENCE WHERE name = 'games'");

    if (query.next())
        return query.value(1).toInt() + 1;
    else
        return -1;
}

int GamesDatabaseModel::getNextSeriesID()
{
    QSqlQuery query(database());
    query.exec("SELECT * FROM SQLITE_SEQUENCE WHERE name = 'series'");

    if (query.next())
        return query.value(1).toInt() + 1;
    else
        return -1;
}

int GamesDatabaseModel::getNextPlatformID()
{
    QSqlQuery query(database());
    query.exec("SELECT * FROM SQLITE_SEQUENCE WHERE name = 'platform'");

    if (query.next())
        return query.value(1).toInt() + 1;
    else
        return -1;
}

bool GamesDatabaseModel::hasSeries(QString series)
{
    return getSeriesID(series) >= 0;
}

bool GamesDatabaseModel::hasPlatform(QString platform)
{
    return getPlatformID(platform) >= 0;
}

bool GamesDatabaseModel::addSeries(QString series)
{
    if (hasSeries(series))
        return false;

    QSqlQuery query(database());
    QString query_string = "INSERT INTO series (name) VALUES ('" + series + "')";
    query.exec(query_string);

    return hasSeries(series);
}

bool GamesDatabaseModel::addPlatform(QString platform)
{
   if (hasPlatform(platform))
       return false;

   QSqlQuery query(database());
   QString query_string = "INSERT INTO platforms (name) VALUES ('" + platform + "')";
   query.exec(query_string);

   return hasPlatform(platform);
}

bool GamesDatabaseModel::addGame(QString title, int series_id, int status_id)
{
    QSqlQuery query = buildAddGameQuery(title, series_id, status_id);
    return execute_query(query);
}

bool GamesDatabaseModel::editGame(int game_id, QString title, int series_id, int status_id)
{
    QSqlQuery query = buildEditGameQuery(game_id, title, series_id, status_id);
    return execute_query(query);
}

bool GamesDatabaseModel::removeGame(int game_id)
{
    QSqlQuery query(database());

    query.prepare("DELETE FROM games WHERE id = :game_id");
    query.bindValue(":game_id", game_id);

    return execute_query(query);
}

// Because there's a variable number of parameters used when adding a game
// to the database, we need to dynamically create a SQL query for doing it.
QSqlQuery GamesDatabaseModel::buildAddGameQuery(QString title, int series_id, int status_id)
{
    QVariantMap game_data;
    game_data.insert("name", title);

    if (series_id >= 0)
        game_data.insert("series_id", series_id);
    if (status_id >= 0)
        game_data.insert("status_id", status_id);

    QString parameters = game_data.keys().join(", ");
    QString placeholders = game_data.keys().join(", :").prepend(':');

    QString query_string = "INSERT INTO games (" + parameters + ") "
            "VALUES (" + placeholders + ")";

    QSqlQuery query(database());
    query.prepare(query_string);

    auto i = game_data.constBegin();
    while (i != game_data.constEnd()) {
        query.bindValue(":" + i.key(), i.value());
        ++i;
    }

    return query;
}

QSqlQuery GamesDatabaseModel::buildEditGameQuery(int game_id, QString title, int series_id, int status_id)
{
    if (game_id < 0)  // Game doesn't exist
        return QSqlQuery();

    QVariantMap game_data;
    game_data.insert("name", title);

    if (series_id >= 0)
        game_data.insert("series_id", series_id);
    if (status_id >= 0)
        game_data.insert("status_id", status_id);

    QStringList parameter_list;
    for (QString param : game_data.keys())
        parameter_list.append(param + " = :" + param);

    QString parameters = parameter_list.join(", ");
    QString query_string = "UPDATE games SET " + parameters + " WHERE id = :game_id";

    QSqlQuery query(database());
    query.prepare(query_string);

    // We add this after everything else to keep the parameter count correct.
    // Also, we don't want to change the game ID when editing entries.
    game_data.insert("game_id", game_id);

    auto i = game_data.constBegin();
    while (i != game_data.constEnd()) {
        query.bindValue(":" + i.key(), i.value());
        ++i;
    }

    return query;
}

bool GamesDatabaseModel::execute_query(QSqlQuery query)
{
    query.exec();

    if (query.lastError().type() == QSqlError::NoError)
        return true;
    else {
        qWarning() << "Database error: " + query.lastError().text();
        return false;
    }
}
