/******************************************************************************
 * log.h : Functions for outputting log messages
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

#include "gbt/log.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>

bool Log::initLogging()
{
    QString log_dir_name = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    Log::log_path = log_dir_name + "/gbt.log";

    if (!QDir(log_dir_name).exists()) {
        QDir().mkpath(log_dir_name);
    }

    QFile log_file(Log::log_path);
    if (log_file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qInstallMessageHandler(handleMessage);
        return true;
    }
    return false;
}

void Log::endLogging()
{
    QFile log_file(Log::log_path);
    log_file.close();
}

void Log::handleMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile log_file(Log::log_path);
    if (!log_file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        return;
    }

    QString timestamp = QDateTime::currentDateTime().toString("[MM-dd-yyyy HH:mm:ss]");
    QString full_msg = timestamp + "(" + Log::msg_type_str[type] + ") " + msg;

    QTextStream stream(&log_file);
    stream << full_msg.toLocal8Bit() << Qt::endl;
}
