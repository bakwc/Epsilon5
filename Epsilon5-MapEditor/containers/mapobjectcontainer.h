// mapobjectcontainer.h
#pragma once
#include "containers/structures.h"
#include "containers/container.h"
#include "containers/mapobjectitem.h"
//------------------------------------------------------------------------------
class TMapObjectContainer : public QObject//TContainer<TMapObjectContainer, TMapObjectItem>
{
public:
    TMapObjectContainer(QObject* parent = 0);
    TMapObjectContainer(TMapObjectContainer* container, QObject* parent = 0);
};
//------------------------------------------------------------------------------
