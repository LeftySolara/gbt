/******************************************************************************
 * dialogaddgame.h : dialog windows for adding games to library
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

#ifndef DIALOGADDGAME_H
#define DIALOGADDGAME_H


#include <QAction>
#include <QComboBox>
#include <QCompleter>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

#include "database/gamesdatabasemodel.h"
#include "uniquefiltermodel.h"

namespace Ui {
class DialogAddGame;
}

class DialogAddGame : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddGame(QWidget *parent = nullptr, GamesDatabaseModel *model = nullptr);
    ~DialogAddGame();

    QLineEdit *line_edit_title;
    QLineEdit *line_edit_series;
    QLineEdit *line_edit_platform;
    QLineEdit *line_edit_genre;
    QLineEdit *line_edit_artwork;
    QPushButton *button_browse;
    QComboBox *combo_box_status;

protected:
    QStringList status_list;
    QCompleter *series_completer;
    QCompleter *platform_completer;
    QCompleter *genre_completer;
    UniqueFilterModel *series_proxy_model;
    UniqueFilterModel *platform_proxy_model;
    UniqueFilterModel *genre_proxy_model;
    Ui::DialogAddGame *ui;

private slots:
    void browseFiles();
};

#endif // DIALOGADDGAME_H
