/******************************************************************************
 * settings.h : helper functions for dealing with program configuration
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

#include "settings.h"

#include <QFile>
#include <QSettings>
#include <QStandardPaths>

QString Settings::getDatabasePath()
{
    QSettings settings;
    return settings.value("database/directory").toString() + "/"
           + settings.value("database/fileName").toString();
}

void Settings::applyDefaultSettings()
{
    QSettings settings;
    QString data_path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    settings.setValue("database/fileName", "games.sqlite");
    settings.setValue("database/directory", data_path);
    settings.setValue("log/fileName", "gbt.log");
    settings.setValue("log/directory", data_path);
}

bool Settings::settingsFileExists()
{
    QSettings settings;
    QFile settings_file(settings.fileName());
    return settings_file.exists();
}
