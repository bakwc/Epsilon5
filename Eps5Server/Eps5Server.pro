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
    application.cpp \
    server.cpp \
    client.cpp \
    ../Eps5World/world.cpp \
    ../Eps5World/player.cpp \
    ../Eps5World/bullet.cpp \
    ../Eps5World/dynamicobject.cpp \
    ../Eps5Proto/Epsilon5.pb.cc

HEADERS += \
    application.h \
    server.h \
    client.h \
    ../Eps5World/world.h \
    ../Eps5World/player.h \
    ../Eps5World/drawableObject.h \
    ../Eps5World/bullet.h \
    ../Eps5World/dynamicobject.h \
    ../Eps5Proto/Epsilon5.pb.h

LIBS += -lprotobuf

OTHER_FILES += \
    ../Eps5Proto/Epsilon5.proto
