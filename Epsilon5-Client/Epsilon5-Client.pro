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
    ../utils/ufullscreenwrapper.cpp \
    main.cpp\
    maindisplay.cpp \
    application.cpp \
    network.cpp \
    imagestorage.cpp \
    map.cpp \
    settings.cpp \
    objects.cpp \
    ../utils/ucast.cpp \
    graphics/basicitem.cpp \
    menu.cpp

HEADERS  += \
    ../Epsilon5-Proto/Epsilon5.pb.h \
    ../Epsilon5-Proto/defines.h \
    ../utils/usettings.h \
    ../utils/uexception.h \
    ../utils/ufullscreenwrapper.h \
    maindisplay.h \
    application.h \
    network.h \
    imagestorage.h \
    map.h \
    settings.h \
    objects.h \
    ../utils/ucast.h \
    graphics/basicitem.h \
    menu.h

FORMS    +=

QMAKE_CXXFLAGS += -std=c++0x
# -march=core2 -mfpmath=sse -Ofast -flto -funroll-loops

LIBS += -lprotobuf

unix {
    VAR=$$(USE_XRANDR)
    !isEmpty(VAR) {
        message( "Using XRANDR extension" )
        DEFINES += USE_XRANDR
        LIBS += -lXrandr
    }
}
win32 {
    LIBS += -luser32
}

OTHER_FILES += \
    ../Epsilon5-Proto/Epsilon5.proto
