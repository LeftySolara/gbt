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

#include <QFileDialog>
#include <QSettings>

#define SERIES_COLUMN 3
#define PLATFORM_COLUMN 4
#define GENRE_COLUMN 5

DialogAddGame::DialogAddGame(QWidget *parent, GamesDatabaseModel *model) :
    QDialog(parent),
    ui(new Ui::DialogAddGame)
{
    ui->setupUi(this);

    combo_box_status = ui->comboBoxStatus;
    line_edit_title = ui->lineEditTitle;
    line_edit_series = ui->lineEditSeries;
    line_edit_platform = ui->lineEditPlatform;
    line_edit_genre = ui->lineEditGenre;
    line_edit_artwork = ui->lineEditArtPath;
    button_browse = ui->pushButtonBrowse;

    // Action for displaying a file browser to select cover art.
    connect(button_browse, SIGNAL(clicked()), this, SLOT(browseFiles()));

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
    // Each LineEdit needs its own proxy model, otherwise the completion
    // data gets combined and mixed up.
    series_proxy_model = new UniqueFilterModel(this);
    series_proxy_model->setSourceModel(model);
    series_proxy_model->setFilterKeyColumn(SERIES_COLUMN);

    series_completer = new QCompleter(series_proxy_model);
    series_completer->setCompletionColumn(SERIES_COLUMN);
    series_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEditSeries->setCompleter(series_completer);


    platform_proxy_model = new UniqueFilterModel(this);
    platform_proxy_model->setSourceModel(model);
    platform_proxy_model->setFilterKeyColumn(PLATFORM_COLUMN);

    platform_completer = new QCompleter(platform_proxy_model);
    platform_completer->setCompletionColumn(PLATFORM_COLUMN);
    platform_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEditPlatform->setCompleter(platform_completer);


    genre_proxy_model = new UniqueFilterModel(this);
    genre_proxy_model->setSourceModel(model);
    genre_proxy_model->setFilterKeyColumn(GENRE_COLUMN);

    genre_completer = new QCompleter(genre_proxy_model);
    genre_completer->setCompletionColumn(GENRE_COLUMN);
    genre_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEditGenre->setCompleter(genre_completer);
}

DialogAddGame::~DialogAddGame()
{
    delete series_completer;
    delete series_proxy_model;
    delete platform_completer;
    delete platform_proxy_model;
    delete genre_completer;
    delete genre_proxy_model;
    delete ui;
}

void DialogAddGame::browseFiles()
{
    QSettings settings;
    QString art_dir = settings.value("art/directory").toString();

    QString art_path = QFileDialog::getOpenFileName(this,
        tr("Select Image"), art_dir, tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));

    line_edit_artwork->setText(art_path);
}
