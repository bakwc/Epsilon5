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
    world.cpp \
    player.cpp \
    bullet.cpp \
    maps.cpp \
    objects.cpp \
    ../utils/ucast.cpp \
    weaponpacks.cpp \
    settings.cpp \
    redisclient.cpp \
    vehicle.cpp \
    ../utils/ucolonsep.cpp \
    ../utils/ucpu.cpp \
    calcs.cpp \
    object.cpp \
    unit.cpp

HEADERS += \
    ../Epsilon5-Proto/Epsilon5.pb.h \
    ../Epsilon5-Proto/defines.h \
    ../utils/usettings.h \
    ../utils/uexception.h \
    application.h \
    server.h \
    client.h \
    world.h \
    player.h \
    bullet.h \
    maps.h \
    objects.h \
    ../utils/ucast.h \
    defines.h \
    weaponpacks.h \
    settings.h \
    redisclient.h \
    vehicle.h \
    ../utils/ucolonsep.h \
    ../utils/umaybe.h \
    calcs.h \
    object.h \
    unit.h \
    object_type.h



QMAKE_CXXFLAGS_RELEASE += -std=c++0x -march=core2 -mfpmath=sse -O3 -flto -funroll-loops
QMAKE_CXXFLAGS_DEBUG += -std=c++0x

LIBS += -lprotobuf -lBox2D -lstdc++

OTHER_FILES += \
    ../Epsilon5-Proto/Epsilon5.proto
