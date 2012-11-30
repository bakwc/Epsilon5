QT += core gui

TARGET = EpsMapGen
TAMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    createmapdialog.cpp \
    mapcreator.cpp \
    graphicsview.cpp \
    mapitem.cpp

HEADERS += \
    mainwindow.h \
    createmapdialog.h \
    mapcreator.h \
    graphicsview.h \
    mapitem.h

FORMS += \
    createmapdialog.ui

QMAKE_CXXFLAGS += -std=c++0x
