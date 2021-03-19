QT += testlib sql
QT -= gui
QTPLUGIN += -plugin-sql-sqlite

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../app/include

SOURCES +=  databaseTest.cpp \
    ../../app/src/log/log.cpp \
    ../../app/src/database/database.cpp

RESOURCES += ../../app/resources/resources.qrc
