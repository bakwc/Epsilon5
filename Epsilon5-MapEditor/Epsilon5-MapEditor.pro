QT += core gui

TARGET = Epsilon5-MapEditor
TEMPLATE = app

SOURCES += \
    ../utils/uexception.cpp \
    ../utils/usettings.cpp \
    ../utils/ucast.cpp \
    main.cpp \
    mainwindow.cpp \
    createmapdialog.cpp \
    mapcreator.cpp \
    graphicsview.cpp \
    mapitem.cpp \
    utils.cpp \
    openmapdialog.cpp \
    mapitemsignal.cpp \
    settings.cpp \
    application.cpp

HEADERS += \
    ../utils/uexception.h \
    ../utils/usettings.h \
    ../utils/ucast.h \
    mainwindow.h \
    createmapdialog.h \
    mapcreator.h \
    graphicsview.h \
    mapitem.h \
    utils.h \
    openmapdialog.h \
    mapitemsignal.h \
    application.h \
    settings.h \
    global.h

FORMS += \
    createmapdialog.ui \
    openmapdialog.ui

QMAKE_CXXFLAGS += -std=c++0x -mfpmath=sse
# -Ofast -flto -funroll-loops
