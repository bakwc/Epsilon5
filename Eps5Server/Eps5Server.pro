#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T21:37:47
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Eps5Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../Eps5Proto/Epsilon5.pb.cc

HEADERS += \
    ../Eps5Proto/Epsilon5.pb.h

LIBS += -lprotobuf
