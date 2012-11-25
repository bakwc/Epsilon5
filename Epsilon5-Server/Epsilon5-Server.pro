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


SOURCES += main.cpp \
    ../Epslion5-Proto/Epsilon5.pb.cc \
    application.cpp \
    server.cpp \
    client.cpp \
    dynamicobject.cpp \
    world.cpp \
    player.cpp \
    bullet.cpp \
    ../utils/usettings.cpp \
    ../utils/uexception.cpp

OTHER_FILES += \
    ../Epslion5-Proto/Epsilon5.proto

HEADERS += \
    ../Epslion5-Proto/Epsilon5.pb.h \
    application.h \
    server.h \
    client.h \
    dynamicobject.h \
    world.h \
    player.h \
    bullet.h \
    ../utils/usettings.h \
    ../utils/uexception.h \
    ../Epslion5-Proto/defines.h

QMAKE_CXXFLAGS += -std=c++0x

LIBS += -lprotobuf -lBox2D
