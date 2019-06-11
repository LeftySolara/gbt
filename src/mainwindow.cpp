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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logutils.h"
#include "dbutils.h"
#include "settings.h"
#include "dialogaddgame.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();

    if (!Settings::settingsFileExists())
        Settings::applyDefaultSettings();

    LogUtils::initLogging();
    initializeDatabaseModel();

    table_view = ui->tableView;
    table_view->setModel(model);
    table_view->hideColumn(0);
    table_view->resizeRowsToContents();
    table_view->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;

    delete exit_act;
    delete addGame_act;
    delete removeGame_act;
    delete aboutQt_act;

    delete library_group;
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
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
    DialogAddGame dialog(nullptr, model);

    if (!dialog.exec())
        return;

    QString title = dialog.line_edit_title->text();
    QString series = dialog.line_edit_series->text();
    int status_id = dialog.combo_box_status->currentIndex();
    int series_id = model->getSeriesID(series);

    if (series_id == -1 && !series.isEmpty())
        model->addSeries(series);

    model->addGame(title, series_id, status_id);
    refreshTableView();
}

void MainWindow::removeGame()
{
    QModelIndex index = table_view->selectionModel()->currentIndex();
    QString game_title = index.sibling(index.row(), 1).data().toString();

    QMessageBox msg_box;
    msg_box.setInformativeText("Remove \"" + game_title + "\" from library?");
    msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg_box.setDefaultButton(QMessageBox::No);
    int rc = msg_box.exec();

    if (rc == QMessageBox::No)
        return;

    int game_id = index.sibling(index.row(), 0).data().toInt();
    model->removeGame(game_id);
    refreshTableView();
}

void MainWindow::createActions()
{
    exit_act = new QAction(tr("&Exit"), this);
    connect(exit_act, &QAction::triggered, this, &MainWindow::exit);

    addGame_act = new QAction(tr("&Add Game"), this);
    connect(addGame_act, &QAction::triggered, this, &MainWindow::addGame);

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

bool MainWindow::isFirstRun()
{
    return (!Settings::settingsFileExists() && !DBUtils::databaseFileExists());
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

    model = new GamesDatabaseModel(nullptr, database);

    if (creating_new_database)
        DBUtils::createDatabaseSchema();

    model->setTable("games");
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setRelation(2, QSqlRelation("status", "id", "name"));
    model->setRelation(3, QSqlRelation("series", "id", "name"));
    model->setHeaderData(1, Qt::Horizontal, "Title");
    model->setHeaderData(2, Qt::Horizontal, "Status");
    model->setHeaderData(3, Qt::Horizontal, "Series");
    model->select();

    return true;
}

void MainWindow::refreshTableView()
{
    model->select();
    table_view->resizeRowsToContents();
}
