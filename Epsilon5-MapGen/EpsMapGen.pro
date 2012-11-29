QT += core gui

TARGET = EpsMapGen
TAMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    createmapdialog.cpp \
    mapcreator.cpp

HEADERS += \
    mainwindow.h \
    createmapdialog.h \
    mapcreator.h

FORMS += \
    createmapdialog.ui

QMAKE_CXXFLAGS += -std=c++0x
