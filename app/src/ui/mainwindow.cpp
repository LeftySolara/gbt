/******************************************************************************
 * mainwindow.cpp : The main UI window
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

#include "gbt/database.h"
#include "gbt/log.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Database::open();
    if (!Database::isOpen()) {
        qCCritical(LOG_GBT) << "Unable to open database.";
    }

    library_ptr.reset(new Library());

    library_table_view.reset(ui->libraryTableView);
    library_table_view->setModel(library_ptr->getModel());
    library_table_view->resizeRowsToContents();
    library_table_view->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
    Database::close();
}

/**
 * @brief Exits the application.
 */
void MainWindow::on_actionQuit_triggered()
{
    qCDebug(LOG_GBT) << "Exit request received. Closing application...";
    QApplication::exit();
}

/**
 * @brief Displays the "About Qt" dialog.
 */
void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}
