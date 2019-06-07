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

#include "gamesdatabasemodel.h"
#include "uniquefiltermodel.h"

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QCompleter>

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
    QComboBox *combo_box_status;

private:
    Ui::DialogAddGame *ui;
    QStringList status_list;
    QCompleter *completer;
    UniqueFilterModel *proxy_model;
};

#endif // DIALOGADDGAME_H
