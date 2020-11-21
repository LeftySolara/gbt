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

#ifndef LOG_H
#define LOG_H

#include <QApplication>
#include <QLoggingCategory>
#include <QMap>

Q_DECLARE_LOGGING_CATEGORY(LOG_GBT);

namespace Log
{
static QString log_path;

static const QMap<QtMsgType, QString> msg_type_str = {
    {QtDebugMsg,    "DEBUG"},
    {QtInfoMsg,     "INFO"},
    {QtWarningMsg,  "WARN"},
    {QtCriticalMsg, "CRITICAL"},
    {QtFatalMsg,    "FATAL"}
};

bool initLogging();
void endLogging();
void handleMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
}

#endif // LOG_H
