#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T21:39:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Eps5Client
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x


SOURCES += main.cpp\
        maindisplay.cpp \
    ../Eps5Proto/Epsilon5.pb.cc \
    application.cpp \
    network.cpp \
    ../Eps5World/world.cpp \
    ../Eps5World/player.cpp

HEADERS  += maindisplay.h \
    ../Eps5Proto/Epsilon5.pb.h \
    application.h \
    network.h \
    ../Eps5World/world.h \
    ../Eps5World/player.h

FORMS    += maindisplay.ui

LIBS += -lprotobuf

OTHER_FILES += \
    ../Eps5Proto/Epsilon5.proto
