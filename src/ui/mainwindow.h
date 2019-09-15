/******************************************************************************
 * mainwindow.h : functionality for the main window UI
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database/gamesdatabasemodel.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QTableView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private slots:
    void exit();
    void aboutQt();
    void addGame();
    void editGame();
    void removeGame();

private:
    void createActions();
    void createMenus();

    bool initializeDatabaseModel();
    void setDatabaseModelRelations();
    void setDatabaseModelHeaders();

    void refreshTableView();

    Ui::MainWindow *ui;

    QSqlDatabase database;
    GamesDatabaseModel *database_model;
    QTableView *library_view;

    QMenu *file_menu;
    QMenu *library_menu;
    QMenu *help_menu;

    QAction *exit_act;
    QAction *addGame_act;
    QAction *editGame_act;
    QAction *removeGame_act;
    QAction *aboutQt_act;

    QActionGroup *library_group;
};

#endif // MAINWINDOW_H
