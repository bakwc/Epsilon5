QT += core gui

TARGET = Epsilon5-MapEditor
TEMPLATE = app

SOURCES += \
    ../utils/uexception.cpp \
    ../utils/usettings.cpp \
    ../utils/ucast.cpp \
    main.cpp \
    mainwindow.cpp \
#    createmapdialog.cpp \
#    mapcreator.cpp \
#    graphicsview.cpp \
#    mapitem.cpp \
#    utils.cpp \
#    openmapdialog.cpp \
#    mapitemsignal.cpp \
    settings.cpp \
    application.cpp \
    imagecache.cpp \
    ui/configurationdialog.cpp \
#    ui/objectseditorform.cpp \
    ui/mapseditorform.cpp \
#    containers/structures.cpp \
#    containers/container.cpp \
#    containers/mapcontainer.cpp \
#    containers/mapobjectcontainer.cpp \
#    containers/maprespawncontainer.cpp \
#    containers/mapobjectitem.cpp \
#    containers/maprespawnitem.cpp \
#    containers/mapitem.cpp \
    graphics/scene.cpp \
    graphics/sceneview.cpp \
    graphics/staticobject.cpp \
    storage/st_mapcontainer.cpp \
    storage/st_mapitem.cpp \
    storage/st_objectcontainer.cpp \
    storage/st_objectitem.cpp \
    storage/st_respawncontainer.cpp \
    storage/st_respawnitem.cpp \
    storage/st_container_t.cpp \
    storage/st_item_t.cpp \
    storage/st_sourceobjectitem.cpp \
    storage/st_sourceobjectcontainer.cpp


HEADERS += \
    ../utils/uexception.h \
    ../utils/usettings.h \
    ../utils/ucast.h \
    mainwindow.h \
#    createmapdialog.h \
#    mapcreator.h \
#    graphicsview.h \
#    mapitem.h \
#    utils.h \
#    openmapdialog.h \
#    mapitemsignal.h \
    application.h \
    settings.h \
    global.h \
    imagecache.h \
    ui/configurationdialog.h \
#    ui/objectseditorform.h \
    ui/mapseditorform.h \
#    containers/mapcontainer.h \
#    containers/structures.h \
#    containers/container.h \
#    containers/mapobjectcontainer.h \
#    containers/maprespawncontainer.h \
#    containers/mapitem.h \
#    containers/mapobjectitem.h \
#    containers/maprespawnitem.h \
    graphics/scene.h \
    graphics/sceneview.h \
    graphics/staticobject.h \
    storage/st_mapcontainer.h \
    storage/st_respawnitem.h \
    storage/st_respawncontainer.h \
    storage/st_objectitem.h \
    storage/st_objectcontainer.h \
    storage/st_mapitem.h \
    storage/st_storageinfo.h \
    storage/st_container_t.h \
    storage/st_item_t.h \
    storage/st_sourceobjectitem.h \
    storage/st_sourceobjectcontainer.h \
    itemmodel_t.h

FORMS += \
#    createmapdialog.ui \
#    openmapdialog.ui \
    ui/configurationdialog.ui \
#    ui/objectseditorform.ui \
    ui/mapseditorform.ui

QMAKE_CXXFLAGS += -std=c++0x
# -mfpmath=sse
# -Ofast -flto -funroll-loops
