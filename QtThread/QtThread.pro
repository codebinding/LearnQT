#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T21:56:30
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = QtThread
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = bin
MOC_DIR = bin
OBJECTS_DIR = bin

SOURCES += main.cpp \
    workerthread.cpp \
    client.cpp

HEADERS += \
    workerthread.h \
    client.h
