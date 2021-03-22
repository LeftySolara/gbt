/******************************************************************************
 * dialogaddgame.cpp : Dialog window for entering new game information.
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


#include "dialogaddgame.h"
#include "ui_dialogaddgame.h"

DialogAddGame::DialogAddGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddGame)
{
    ui->setupUi(this);

    line_edit_title_ptr.reset(ui->lineEdit_title);
}

DialogAddGame::~DialogAddGame()
{
    delete ui;
}
