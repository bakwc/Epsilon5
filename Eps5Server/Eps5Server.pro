#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T21:37:47
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = Eps5Server
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app


SOURCES += main.cpp \
    ../Eps5Proto/Epsilon5.pb.cc \
    application.cpp \
    server.cpp \
    ../Eps5World/world.cpp \
    client.cpp \
    ../Eps5World/player.cpp

HEADERS += \
    ../Eps5Proto/Epsilon5.pb.h \
    application.h \
    server.h \
    ../Eps5World/world.h \
    client.h \
    ../Eps5World/player.h

LIBS += -lprotobuf

OTHER_FILES += \
    ../Eps5Proto/Epsilon5.proto
