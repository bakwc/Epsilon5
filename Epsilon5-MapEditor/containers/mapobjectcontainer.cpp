// mapobjectcontainer.cpp
#include "containers/mapobjectcontainer.h"
//------------------------------------------------------------------------------
TMapObjectContainer::TMapObjectContainer(QObject* parent)
//    : TContainer(parent)
    : QObject(parent)
{
}
//------------------------------------------------------------------------------
TMapObjectContainer::TMapObjectContainer(TMapObjectContainer* container,
        QObject* parent)
//    : TContainer(parent)
    : QObject(parent)
{
}
//------------------------------------------------------------------------------
