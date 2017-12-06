#-------------------------------------------------
#
# Project created by QtCreator 2017-06-30T20:46:36
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include($$PWD/Graphics/Graphics.pri)
include($$PWD/Application/application.pri)

CONFIG += c++11

TARGET =Graphics
TEMPLATE = app

SOURCES += main.cpp

HEADERS  +=

FORMS    +=

RESOURCES += \
    image.qrc
