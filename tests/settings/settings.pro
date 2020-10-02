QT += testlib sql
QT -= gui
QTPLUGIN += -plugin-sql-sqlite

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../app/include

SOURCES +=  settingsTest.cpp
