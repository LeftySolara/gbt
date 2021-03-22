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

#include <QMessageBox>

#include "gbt/database.h"
#include "gbt/log.h"
#include "dialogaddgame.h"

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

    library_table_view_ptr.reset(ui->libraryTableView);
    library_table_view_ptr->setModel(library_ptr->getModel());
    refreshLibraryView();

    connect(ui->actionAboutQt, &QAction::triggered, this, &MainWindow::showAboutQt);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quit);
    connect(ui->actionAddGame, &QAction::triggered, this, &MainWindow::showDialogAddGame);
    connect(ui->actionRemoveGame, &QAction::triggered, this, &MainWindow::removeGame);
}

MainWindow::~MainWindow()
{
    delete ui;
    Database::close();
}

/**
 * @brief Exits the application.
 */
void MainWindow::quit()
{
    qCDebug(LOG_GBT) << "Exit request received. Closing application...";
    QApplication::exit();
}

/**
 * @brief Displays the "About Qt" dialog.
 */
void MainWindow::showAboutQt()
{
    QApplication::aboutQt();
}

/**
 * @brief Displays the "Add Game" dialog.
 */
void MainWindow::showDialogAddGame()
{
    DialogAddGame dialog = DialogAddGame();

    if (!dialog.exec()) {
        return;
    }

    QString title = dialog.line_edit_title_ptr->text();
    library_ptr->addGame(title);
    refreshLibraryView();
}

/**
 * @brief Removes the currently selected game from the library.
 */
void MainWindow::removeGame()
{
    QModelIndex index = library_table_view_ptr->selectionModel()->currentIndex();
    QString game_title = index.sibling(index.row(), 1).data().toString();

    QMessageBox msg_box;
    msg_box.setInformativeText("Remove \"" + game_title + "\" from library?");
    msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg_box.setDefaultButton(QMessageBox::No);

    int rc = msg_box.exec();
    if (rc == QMessageBox::No) {
        return;
    }

    const unsigned int game_id = index.sibling(index.row(), 0).data().toUInt();
    library_ptr->removeGame(game_id);
    refreshLibraryView();
}

/**
 * @brief Updates the TableView with changes made to the database mode.
 */
void MainWindow::refreshLibraryView()
{
    library_ptr->getModel()->select();
    library_table_view_ptr->resizeRowsToContents();
    library_table_view_ptr->resizeColumnsToContents();
}
