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

#include <QStandardPaths>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LogUtils::initLogging();

    settings = new QSettings();
    bool first_run = isFirstRun();

    if (first_run)
        applyDefaultSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
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
