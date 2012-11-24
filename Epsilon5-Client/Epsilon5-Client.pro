#-------------------------------------------------
#
# Project created by QtCreator 2012-11-23T08:05:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Epsilon5-Client
TEMPLATE = app


SOURCES += main.cpp\
        maindisplay.cpp \
    ../Epslion5-Proto/Epsilon5.pb.cc \
    application.cpp \
    network.cpp \
    imagestorage.cpp \
    map.cpp \
    settings.cpp

HEADERS  += maindisplay.h \
    ../Epslion5-Proto/Epsilon5.pb.h \
    application.h \
    network.h \
    imagestorage.h \
    map.h \
    settings.h

FORMS    +=

QMAKE_CXXFLAGS += -std=c++0x

LIBS += -lprotobuf

OTHER_FILES += \
    ../Epslion5-Proto/Epsilon5.proto
