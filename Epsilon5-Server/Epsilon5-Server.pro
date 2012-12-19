#-------------------------------------------------
#
# Project created by QtCreator 2012-11-23T08:04:48
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = Epsilon5-Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += EPSILON_SERVER


SOURCES += main.cpp \
    ../Epsilon5-Proto/Epsilon5.pb.cc \
    ../utils/usettings.cpp \
    ../utils/uexception.cpp \
    application.cpp \
    server.cpp \
    client.cpp \
    dynamicobject.cpp \
    world.cpp \
    player.cpp \
    bullet.cpp \
    maps.cpp \
    objects.cpp \
    staticobject.cpp \
    ../utils/ucast.cpp \
    weaponpacks.cpp \
    settings.cpp \
    redisclient.cpp

HEADERS += \
    ../Epsilon5-Proto/Epsilon5.pb.h \
    ../Epsilon5-Proto/defines.h \
    ../utils/usettings.h \
    ../utils/uexception.h \
    application.h \
    server.h \
    client.h \
    dynamicobject.h \
    world.h \
    player.h \
    bullet.h \
    maps.h \
    objects.h \
    staticobject.h \
    ../utils/ucast.h \
    defines.h \
    weaponpacks.h \
    settings.h \
    redisclient.h

QMAKE_CXXFLAGS += -std=c++0x -march=core2 -mfpmath=sse -Ofast -flto -funroll-loops

LIBS += -lprotobuf -lBox2D

OTHER_FILES += \
    ../Epsilon5-Proto/Epsilon5.proto
