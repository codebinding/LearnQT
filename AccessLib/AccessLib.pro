#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T10:14:18
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = AccessLib
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp

HEADERS += \
    client.h

unix:!macx: LIBS += -L$$PWD/lib/ -lMath

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix:!macx: PRE_TARGETDEPS += $$PWD/lib/libMath.a
