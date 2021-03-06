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

#include <QDebug>
#include <QFile>
#include <QImage>
#include <QPixmap>
#include <QSqlError>
#include <QSqlQuery>
#include <QTextStream>
#include <QVector>

#include "dbutils.h"

GamesDatabaseModel::GamesDatabaseModel(QObject *parent, QSqlDatabase db)
    : QSqlRelationalTableModel(parent)
{
}

QVariant GamesDatabaseModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // Display cover art in the view directly
    if (index.column() == DBUtils::Column::ART_PATH) {
        QString img_file_path = QSqlRelationalTableModel::data(index, Qt::DisplayRole).toString();

        if (role == Qt::DisplayRole)
            return QString();

        QImage image(img_file_path);
        QPixmap pixmap = QPixmap::fromImage(
                    image.scaledToHeight(100, Qt::SmoothTransformation));

        if (role == Qt::DecorationRole)
            return pixmap;
        if (role == Qt::SizeHintRole)
            return pixmap.size();
    }

    return QSqlRelationalTableModel::data(index, role);
}

QVariant GamesDatabaseModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    if (section == DBUtils::Column::ART_PATH)
        return "Artwork";

    return QSqlRelationalTableModel::headerData(section, orientation, role);
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

int GamesDatabaseModel::getGenreID(QString genre)
{
    QSqlQuery query(database());
    QString query_string = "SELECT * FROM genres WHERE name = '" + genre + "'";
    query.exec(query_string);

    if (query.next()) {
        int id = query.value(0).toInt();
        int next_id = getNextGenreID();

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
    query.exec("SELECT * FROM SQLITE_SEQUENCE WHERE name = 'platforms'");

    if (query.next())
        return query.value(1).toInt() + 1;
    else
        return -1;
}

int GamesDatabaseModel::getNextGenreID()
{
    QSqlQuery query(database());
    query.exec("SELECT * FROM SQLITE_SEQUENCE WHERE name = 'genres'");

    if (query.next())
        return query.value(1).toInt() + 1;
    else
        return -1;
}

bool GamesDatabaseModel::hasGame(QString title)
{
    return getGameID(title) >= 0;
}

bool GamesDatabaseModel::hasSeries(QString series)
{
    return getSeriesID(series) >= 0;
}

bool GamesDatabaseModel::hasPlatform(QString platform)
{
    return getPlatformID(platform) >= 0;
}

bool GamesDatabaseModel::hasGenre(QString genre)
{
    return getGenreID(genre) >= 0;
}

bool GamesDatabaseModel::addGame(struct GameData game_data)
{
    if (hasGame(game_data.title))
        return false;

    validateGameData(game_data);
    QSqlQuery query = buildAddGameQuery(game_data);
    return executeQuery(query);
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

bool GamesDatabaseModel::addGenre(QString genre)
{
    if (hasGenre(genre))
        return false;

    QSqlQuery query(database());
    QString query_string = "INSERT INTO genres (name) VALUES ('" + genre + "')";
    query.exec(query_string);

    return hasGenre(genre);
}

bool GamesDatabaseModel::editGame(struct GameData game_data)
{
    if (!hasGame(game_data.title))
        return false;

    validateGameData(game_data);
    QSqlQuery query = buildEditGameQuery(game_data);
    return executeQuery(query);
}

bool GamesDatabaseModel::removeGame(int game_id)
{
    QSqlQuery query(database());
    query.prepare("DELETE FROM games WHERE id = :game_id");
    query.bindValue(":game_id", game_id);

    return executeQuery(query);
}

// Checks the given game data for existing database entries.
// If a field is given and there's currently no entry, one is added.
void GamesDatabaseModel::validateGameData(GameData game_data)
{
    QString series = game_data.series;
    if (!series.isEmpty() && !hasSeries(series))
        addSeries(series);

    QString platform = game_data.platform;
    if (!platform.isEmpty() && !hasPlatform(platform))
        addPlatform(platform);

    QString genre = game_data.genre;
    if (!genre.isEmpty() && !hasGenre(genre))
        addGenre(genre);
}

QSqlQuery GamesDatabaseModel::buildAddGameQuery(struct GameData game_data)
{
    QVariantMap query_data;
    int status_id = game_data.status_id;
    int series_id = getSeriesID(game_data.series);
    int platform_id = getPlatformID(game_data.platform);
    int genre_id = getGenreID(game_data.genre);

    query_data.insert("name", game_data.title);
    if (series_id >= 0)
        query_data.insert("series_id", series_id);
    if (status_id >= 0)
        query_data.insert("status_id", status_id);
    if (platform_id >= 0)
        query_data.insert("platform_id", platform_id);
    if (genre_id >= 0)
        query_data.insert("genre_id", genre_id);
    if (!game_data.art_path.isEmpty())
        query_data.insert("art_path", game_data.art_path);

    QString parameters = query_data.keys().join(", ");
    QString placeholders = query_data.keys().join(", :").prepend(':');

    QString query_string = "INSERT INTO games (" + parameters + ") "
            "VALUES (" + placeholders + ")";

    QSqlQuery query(database());
    query.prepare(query_string);

    auto i = query_data.constBegin();
    while (i != query_data.constEnd()) {
        query.bindValue(":" + i.key(), i.value());
        ++i;
    }

    return query;
}

QSqlQuery GamesDatabaseModel::buildEditGameQuery(GameData game_data)
{
    QVariantMap query_data;
    int status_id = game_data.status_id;
    int series_id = getSeriesID(game_data.series);
    int platform_id = getPlatformID(game_data.platform);
    int genre_id = getGenreID(game_data.genre);

    query_data.insert("name", game_data.title);
    query_data.insert("series_id", series_id);
    query_data.insert("status_id", status_id);
    query_data.insert("platform_id", platform_id);
    query_data.insert("genre_id", genre_id);
    query_data.insert("art_path", game_data.art_path);

    QStringList parameter_list;
    for (QString param : query_data.keys())
        parameter_list.append(param + " = :" + param);

    QString parameters = parameter_list.join(", ");
    QString query_string = "UPDATE games SET " + parameters + " WHERE id = :game_id";

    QSqlQuery query(database());
    query.prepare(query_string);

    // We add this after everything else to keep the parameter count correct.
    // Also, we don't want to change the game ID when editing entries.
    query_data.insert("game_id", game_data.id);

    auto i = query_data.constBegin();
    while (i != query_data.constEnd()) {
        query.bindValue(":" + i.key(), i.value());
        ++i;
    }

    return query;
}

bool GamesDatabaseModel::executeQuery(QSqlQuery query)
{
    query.exec();

    if (query.lastError().type() == QSqlError::NoError)
        return true;
    else {
        qWarning() << "Database error: " + query.lastError().text();
        return false;
    }
}

