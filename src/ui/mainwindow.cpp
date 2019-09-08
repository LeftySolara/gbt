/******************************************************************************
 * mainwindow.cpp : functionality for the main window UI
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

#include "ui/mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QMessageBox>
#include <QSettings>

#include "database/dbutils.h"
#include "logging/logutils.h"
#include "settings/settings.h"
#include "ui/dialogaddgame.h"
#include "ui/dialogeditgame.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings settings;
    QString art_path = settings.value("art/directory").toString();
    if (!QDir(art_path).exists())
        QDir().mkpath(art_path);

    setWindowTitle("Game Backlog Tracker");

    createActions();
    createMenus();

    initializeDatabaseModel();

    library_view = ui->tableView;
    library_view->setModel(database_model);
    library_view->hideColumn(0);
    library_view->sortByColumn(1, Qt::AscendingOrder);
    library_view->resizeRowsToContents();
    library_view->resizeColumnsToContents();

    QHeaderView *header = library_view->horizontalHeader();
    header->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete database_model;

    delete exit_act;
    delete addGame_act;
    delete editGame_act;
    delete removeGame_act;
    delete aboutQt_act;

    delete library_group;
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(editGame_act);
    menu.addAction(removeGame_act);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::exit()
{
    QApplication::exit();
}

void MainWindow::aboutQt()
{
    QApplication::aboutQt();
}

void MainWindow::addGame()
{
    DialogAddGame dialog(nullptr, database_model);

    if (!dialog.exec())
        return;

    struct GameData game_data;
    game_data.title = dialog.line_edit_title->text();
    game_data.series = dialog.line_edit_series->text();
    game_data.platform = dialog.line_edit_platform->text();
    game_data.status_id = dialog.combo_box_status->currentIndex();
    game_data.genre = dialog.line_edit_genre->text();
    game_data.art_path = dialog.line_edit_artwork->text();

    database_model->addGame(game_data);
    refreshTableView();
}

void MainWindow::editGame()
{
    QModelIndex index = library_view->currentIndex();
    DialogEditGame dialog(nullptr, database_model, index);

    if (!dialog.exec())
        return;

    struct GameData game_data;

    // SQLite uses single quotes to enclose strings, so we need to escape them.
    game_data.id = database_model->getGameID(dialog.line_edit_title->text().replace("'", "''"));
    game_data.series = dialog.line_edit_series->text().replace("'", "''");
    game_data.title = dialog.line_edit_title->text();
    game_data.platform = dialog.line_edit_platform->text();
    game_data.status_id = dialog.combo_box_status->currentIndex();
    game_data.genre = dialog.line_edit_genre->text();
    game_data.art_path = dialog.line_edit_artwork->text();

    database_model->editGame(game_data);
    refreshTableView();
}

void MainWindow::removeGame()
{
    QModelIndex index = library_view->selectionModel()->currentIndex();
    QString game_title = index.sibling(index.row(), 1).data().toString();

    QMessageBox msg_box;
    msg_box.setInformativeText("Remove \"" + game_title + "\" from library?");
    msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg_box.setDefaultButton(QMessageBox::No);
    int rc = msg_box.exec();

    if (rc == QMessageBox::No)
        return;

    int game_id = index.sibling(index.row(), 0).data().toInt();
    database_model->removeGame(game_id);
    refreshTableView();
}

void MainWindow::createActions()
{
    exit_act = new QAction(tr("&Exit"), this);
    connect(exit_act, &QAction::triggered, this, &MainWindow::exit);

    addGame_act = new QAction(tr("&Add Game"), this);
    connect(addGame_act, &QAction::triggered, this, &MainWindow::addGame);

    editGame_act = new QAction(tr("&Edit Game"), this);
    connect(editGame_act, &QAction::triggered, this, &MainWindow::editGame);

    removeGame_act = new QAction(tr("&Remove Game"), this);
    connect(removeGame_act, &QAction::triggered, this, &MainWindow::removeGame);

    aboutQt_act = new QAction(tr("&About Qt..."), this);
    connect(aboutQt_act, &QAction::triggered, this, &MainWindow::aboutQt);

    library_group = new QActionGroup(this);
    library_group->addAction(addGame_act);
    library_group->addAction(removeGame_act);
}

void MainWindow::createMenus()
{
    file_menu = menuBar()->addMenu(tr("&File"));
    file_menu->addAction(exit_act);

    library_menu = menuBar()->addMenu(tr("&Library"));
    library_menu->addAction(addGame_act);
    library_menu->addAction(removeGame_act);

    help_menu = menuBar()->addMenu(tr("&Help"));
    help_menu->addAction(aboutQt_act);
}

bool MainWindow::initializeDatabaseModel()
{
    bool creating_new_database = !DBUtils::databaseFileExists();
    if (creating_new_database) {
        qInfo("No database file found. Attempting to create...");
        DBUtils::createDatabaseFile();
    }

    database = DBUtils::initializeDatabaseConnection();
    if (!database.open()) {
        qCritical("Error: could not connect to database.");
        return false;
    }

    // Call this after everything else since the database needs to be open first.
    if (creating_new_database)
        DBUtils::createDatabaseSchema();

    database_model = new GamesDatabaseModel(nullptr, database);
    database_model->setTable("games");
    database_model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    setDatabaseModelRelations();

    database_model->select();

    return true;
}

void MainWindow::setDatabaseModelRelations()
{
    database_model->setRelation(2, QSqlRelation("status", "id", "name"));
    database_model->setRelation(3, QSqlRelation("series", "id", "name"));
    database_model->setRelation(4, QSqlRelation("platforms", "id", "name"));
    database_model->setRelation(5, QSqlRelation("genres", "id", "name"));

    database_model->setHeaderData(1, Qt::Horizontal, "Title");
    database_model->setHeaderData(2, Qt::Horizontal, "Status");
    database_model->setHeaderData(3, Qt::Horizontal, "Series");
    database_model->setHeaderData(4, Qt::Horizontal, "Platform");
    database_model->setHeaderData(5, Qt::Horizontal, "Genre");
    database_model->setHeaderData(6, Qt::Horizontal, "Cover Art", Qt::DecorationRole);
}

void MainWindow::refreshTableView()
{
    database_model->select();
    library_view->resizeRowsToContents();
}
