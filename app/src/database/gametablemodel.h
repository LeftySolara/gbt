/******************************************************************************
 * gametablemodel.h : Editable data model for the game table
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

#ifndef GAMETABLEMODEL_H
#define GAMETABLEMODEL_H

#include <QSqlRelationalTableModel>


class GameTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT

public:
    explicit GameTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool addGame(const QString title) const;

private:
    bool gameExists(const QString title) const;

    int getGameID(const QString title) const;
    int getNextGameID() const;
};

#endif // GAMETABLEMODEL_H
