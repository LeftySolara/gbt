/******************************************************************************
 * dialogaddgame.h : dialog windows for editing games in library
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

#ifndef DIALOGEDITGAME_H
#define DIALOGEDITGAME_H

#include "dialogaddgame.h"
#include "ui_dialogaddgame.h"

namespace Ui {
class DialogEditGame;
}

class DialogEditGame : public DialogAddGame
{
    Q_OBJECT

public:
    explicit DialogEditGame(QWidget *parent = nullptr, GamesDatabaseModel *model = nullptr,
                            const QModelIndex &index = QModelIndex());
};

#endif // DIALOGEDITGAME_H
