#-------------------------------------------------
#
# Build configuration for gbt
#
#-------------------------------------------------

QT       += core gui widgets sql
QTPLUGIN += -plugin-sql-sqlite

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = gbt
TEMPLATE = app
CONFIG += c++17
VERSION = 0.1
DEFINES += APP_VERSION=\\\"$VERSION\\\"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += src

SOURCES += \
        src/database/dbutils.cpp \
        src/database/gamesdatabasemodel.cpp \
        src/logging/logutils.cpp \
        src/main.cpp \
        src/settings/settings.cpp \
        src/ui/dialogaddgame.cpp \
        src/ui/dialogeditgame.cpp \
        src/ui/mainwindow.cpp \
        src/ui/uniquefiltermodel.cpp

HEADERS += \
        src/database/dbutils.h \
        src/database/gamesdatabasemodel.h \
        src/logging/logutils.h \
        src/settings/settings.h \
        src/ui/dialogaddgame.h \
        src/ui/dialogeditgame.h \
        src/ui/mainwindow.h \
        src/ui/uniquefiltermodel.h

FORMS += \
        src/ui/dialogaddgame.ui \
        src/ui/mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
