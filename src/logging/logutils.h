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

#ifndef LOGUTILS_H
#define LOGUTILS_H

#include <QApplication>
#include <QFile>
#include <QStandardPaths>

namespace LogUtils
{
    bool initLogging();
    void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
}

#endif // LOGUTILS_H
