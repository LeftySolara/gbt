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

#include "gametablemodel.h"

/**
 * @brief Constructor for GameTableModel. Uses the constructor inherited from QSqlRelationalTableModel.
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
