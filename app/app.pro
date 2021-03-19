#------------------------------------------------
#
# Build configuration for gbt
#
#------------------------------------------------

QT += core gui sql
QTPLUGIN += -plugin-sql-sqlite

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gbt
TEMPLATE = app
CONFIG += c++17
VERSION = 0.0.1

DEFINES += APP_VERSION\\\"$VERSION\\\"
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += src include

SOURCES += \
    src/database/database.cpp \
    src/database/gametablemodel.cpp \
    src/library/library.cpp \
    src/main.cpp \
    src/log/log.cpp \
    src/ui/mainwindow.cpp

HEADERS += \
    include/gbt/database.h \
    include/gbt/library.h \
    include/gbt/log.h \
    src/database/gametablemodel.h \
    src/ui/mainwindow.h

FORMS += \
    src/ui/mainwindow.ui

RESOURCES += \
    resources/resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

