/******************************************************************************
 * dialogaddgame.cpp : dialog windows for adding games to library
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

#include "dialogaddgame.h"
#include "ui_dialogaddgame.h"

#define SERIES_COLUMN 3

DialogAddGame::DialogAddGame(QWidget *parent, GamesDatabaseModel *model) :
    QDialog(parent),
    ui(new Ui::DialogAddGame)
{
    ui->setupUi(this);
    combo_box_status = ui->comboBoxStatus;
    line_edit_title = ui->lineEditTitle;
    line_edit_series = ui->lineEditSeries;

    // We'll add options to the combo box using string literals.
    // We could set the combo box to use the database model, but that
    // changes the table and prevents other functions from accessing
    // data from other tables. Since there are only five possible
    // statuses, doing it this way isn't too bad for now.
    status_list  << "Not Started" << "Playing" << "Finished" << "On Hold" << "Dropped";
    combo_box_status->addItems(status_list);

    // To set up auto completions, we need to use a proxy model.
    // That way we can filter out duplicates without altering
    // the actual underlying data.
    proxy_model = new UniqueFilterModel(this);
    proxy_model->setSourceModel(model);
    proxy_model->setFilterKeyColumn(SERIES_COLUMN);

    completer = new QCompleter(proxy_model);
    completer->setCompletionColumn(SERIES_COLUMN);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEditSeries->setCompleter(completer);
}

DialogAddGame::~DialogAddGame()
{
    delete completer;
    delete proxy_model;
    delete ui;
}
