/******************************************************************************
 * uniquefiltermodel.h : filter for removing duplicate items from combo boxes
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

#ifndef UNIQUEFILTERMODEL_H
#define UNIQUEFILTERMODEL_H

#include <QSortFilterProxyModel>

class UniqueFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit UniqueFilterModel(QObject *parent = nullptr);
    ~UniqueFilterModel() override;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QStringList *unique_rows;
};

#endif // UNIQUEFILTERMODEL_H
