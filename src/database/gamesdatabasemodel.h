/******************************************************************************
 * gamesdatabasemodel.h : data model for the games database
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

#ifndef GAMESDATABASEMODEL_H
#define GAMESDATABASEMODEL_H

#include <QSqlRelationalTableModel>


struct GameData {
    int id;
    int status_id;
    QString title;
    QString series;
    QString platform;
    QString genre;
    QString art_path;
};

class GamesDatabaseModel : public QSqlRelationalTableModel
{
    Q_OBJECT

public:
    explicit GamesDatabaseModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int getGameID(QString title);
    int getSeriesID(QString series);
    int getPlatformID(QString platform);
    int getGenreID(QString genre);

    int getNextGameID();
    int getNextSeriesID();
    int getNextPlatformID();
    int getNextGenreID();

    bool hasGame(QString title);
    bool hasSeries(QString series);
    bool hasPlatform(QString platform);
    bool hasGenre(QString genre);

    bool addGame(struct GameData game_data);
    bool addSeries(QString series);
    bool addPlatform(QString platform);
    bool addGenre(QString genre);

    bool editGame(struct GameData game_data);

    bool removeGame(int game_id);

private:
    void validateGameData(struct GameData game_data);

    QSqlQuery buildAddGameQuery(struct GameData game_data);
    QSqlQuery buildEditGameQuery(struct GameData game_data);
    bool executeQuery(QSqlQuery query);
};

#endif // GAMESDATABASEMODEL_H
