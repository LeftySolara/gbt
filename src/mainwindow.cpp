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

#include <QSqlQuery>
#include <QStandardPaths>
#include <QTextStream>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new QSettings();
    bool first_run = isFirstRun();

    if (first_run)
        applyDefaultSettings();

    LogUtils::initLogging();

    QString database_path = settings->value("database/directory").toString() +
            "/" + settings->value("database/fileName").toString();

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(database_path);

    if (!database.open()) {
        qCritical("Error: could not open database.");
        return;
    }

    if (first_run) {
        // Create the database schema and populate tables.
        // If a debug build is running, populate the database with sample data.
        QString init_script_path;
        #ifdef QT_DEBUG
            init_script_path = "../../gbt/scripts/init_db_sample_data.sql";
        #else
            init_script_path = "../../gbt/scripts/init_db.sql";
        #endif

        if (executeSqlScript(init_script_path))
            qInfo("Successfully created and initialized database.");
        else {
            qCritical("Error: failed to create database.");
            return;
        }
    }

    model = new QSqlRelationalTableModel(nullptr, database);

    model->setTable("games");
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setRelation(2, QSqlRelation("status", "id", "name"));
    model->setRelation(3, QSqlRelation("series", "id", "name"));
    model->setHeaderData(1, Qt::Horizontal, "Title");
    model->setHeaderData(2, Qt::Horizontal, "Status");
    model->setHeaderData(3, Qt::Horizontal, "Series");
    model->select();

    table_view = ui->tableView;
    table_view->setModel(model);
    table_view->hideColumn(0);
    table_view->resizeRowsToContents();
    table_view->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
    delete model;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

bool MainWindow::isFirstRun()
{
    return (!settingsFileExists() && !databaseFileExists());
}

bool MainWindow::settingsFileExists()
{
    QFile settings_file(settings->fileName());
    return settings_file.exists();
}

bool MainWindow::databaseFileExists()
{
    if (!settingsFileExists())
        return false;

    QString db_path = settings->value("database/directory").toString() +
            "/" + settings->value("database/fileName").toString();
    QFile db_file(db_path);

    return db_file.exists();
}

void MainWindow::applyDefaultSettings()
{
    QString data_path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    settings->setValue("database/fileName", "games.sqlite");
    settings->setValue("database/directory", data_path);
    settings->setValue("log/fileName", "gbt.log");
    settings->setValue("log/directory", data_path);
}

bool MainWindow::executeSqlScript(QString script_path)
{
    QFile script(script_path);
    if (!script.open(QIODevice::ReadOnly))
        return false;

    QString line;
    QString sql_statement = "";
    QTextStream stream(&script);
    QSqlQuery query;

    while (!stream.atEnd()) {
        line = stream.readLine();
        if (line.startsWith("--") || line.length() == 0) // ignore comments
            continue;

        sql_statement += line;
        if (sql_statement.endsWith(";")) {
            sql_statement.chop(1);  // remove trailing semicolon
            if (query.prepare(sql_statement)) {
                query.exec();
                sql_statement = "";
            }
            else
                return false;
        }
    }
    script.close();
    return true;
}
