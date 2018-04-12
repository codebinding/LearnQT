#-------------------------------------------------
#
# Project created by QtCreator 2018-03-27T20:37:24
#
#-------------------------------------------------

QT       -= core gui

TARGET = Math
TEMPLATE = lib
CONFIG += staticlib

SOURCES += math.cpp

HEADERS += math.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
