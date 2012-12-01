#-------------------------------------------------
#
# Project created by QtCreator 2012-11-23T08:05:49
#
#-------------------------------------------------

QT       += core gui network opengl

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
    settings.cpp \
    objects.cpp

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
    settings.h \
    objects.h

FORMS    +=

QMAKE_CXXFLAGS += -std=c++0x -march=core2 -mfpmath=sse -Ofast -flto -funroll-loops

LIBS += -lprotobuf

OTHER_FILES += \
    ../Epsilon5-Proto/Epsilon5.proto
