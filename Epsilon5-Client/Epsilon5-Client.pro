#-------------------------------------------------
#
# Project created by QtCreator 2012-11-23T08:05:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Epsilon5-Client
TEMPLATE = app

SOURCES += \
    ../Epsilon5-Proto/Epsilon5.pb.cc \
    ../utils/usettings.cpp \
    ../utils/uexception.cpp \
    main.cpp\
    maindisplay.cpp \
    application.cpp \
    network.cpp \
    imagestorage.cpp \
    map.cpp \
    settings.cpp

HEADERS  += \
    ../Epsilon5-Proto/Epsilon5.pb.h \
    ../Epsilon5-Proto/defines.h \
    ../utils/usettings.h \
    ../utils/uexception.h \
    maindisplay.h \
    application.h \
    network.h \
    imagestorage.h \
    map.h \
    settings.h

FORMS    +=

QMAKE_CXXFLAGS += -std=c++0x

LIBS += -lprotobuf

OTHER_FILES += \
    ../Epsilon5-Proto/Epsilon5.proto
