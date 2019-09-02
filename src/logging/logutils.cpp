/******************************************************************************
 * logutils.h : functions for logging
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

#include "logutils.h"

#include <QSettings>
#include <QDateTime>
#include <QTextStream>
#include <QDir>

bool LogUtils::initLogging()
{
    QSettings settings;
    QString log_dir_name = settings.value("log/directory").toString();
    QString log_file_name = settings.value("log/fileName").toString();

    if (!QDir(log_dir_name).exists())
        QDir().mkpath(log_dir_name);

    QFile log_file(log_dir_name + "/" + log_file_name);
    if (log_file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qInstallMessageHandler(outputMessage);
        return true;
    }
    else
        return false;
}

void LogUtils::outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QSettings settings;
    QString log_dir_name = settings.value("log/directory").toString();
    QString log_file_name = settings.value("log/fileName").toString();

    QFile log_file(log_dir_name + "/" + log_file_name);
    log_file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream log_stream(&log_file);

    QString msg_type_str;
    switch(type) {
    case QtDebugMsg:
        msg_type_str = "Debug";
        break;
    case QtInfoMsg:
        msg_type_str = "Info";
        break;
    case QtWarningMsg:
        msg_type_str = "Warning";
        break;
    case QtCriticalMsg:
        msg_type_str = "Critical";
        break;
    case QtFatalMsg:
        msg_type_str = "Fatal";
        break;
    }

    QString date_time_stamp = QDateTime::currentDateTime().toString("[MM-dd-yyyy HH:mm:ss]");
    QString local_msg = date_time_stamp + " " + msg_type_str + ": " + msg;
    log_stream << local_msg.toLocal8Bit() << endl;
}
