/******************************************************************************
 * dialogaddgame.h : Dialog window for entering new game information.
 * ****************************************************************************
 * Copyright (C) 2020 Jalen Adams
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

#include <QDialog>
#include <QLineEdit>
#include <QScopedPointer>

namespace Ui {
class DialogAddGame;
}

class DialogAddGame : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddGame(QWidget *parent = nullptr);
    ~DialogAddGame();

    QScopedPointer<QLineEdit> lineEdit_title_ptr;

private:
    Ui::DialogAddGame *ui;
};

#endif // DIALOGADDGAME_H
