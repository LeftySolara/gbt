/******************************************************************************
 * dialogaddgame.cpp : dialog windows for editing games in library
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

#include "dialogeditgame.h"

#define TITLE_COLUMN 1
#define STATUS_COLUMN 2
#define SERIES_COLUMN 3

DialogEditGame::DialogEditGame(QWidget *parent, GamesDatabaseModel *model, const QModelIndex &index) :
    DialogAddGame(parent, model)
{
    line_edit_title = ui->lineEditTitle;
    line_edit_series = ui->lineEditSeries;
    combo_box_status = ui->comboBoxStatus;

    QString title = index.sibling(index.row(), TITLE_COLUMN).data().toString();
    QString series = index.sibling(index.row(), SERIES_COLUMN).data().toString();
    QString status = index.sibling(index.row(), STATUS_COLUMN).data().toString();

    line_edit_title->setText(title);
    line_edit_series->setText(series);
    combo_box_status->setCurrentIndex(status_list.indexOf(status));
}
