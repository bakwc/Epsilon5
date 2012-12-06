// mapobjectcontainer.h
#pragma once
#include "containers/structures.h"
#include "containers/container.h"
#include "containers/mapobjectitem.h"
//------------------------------------------------------------------------------
class TMapObjectContainer : public TContainer
{
public:
    TMapObjectContainer(QObject* parent = 0);
    TMapObjectContainer(const TMapObjectContainer& container);
    ~TMapObjectContainer();
    void addObject(const TMapObjectInfo& info);
    void removeObject(const QModelIndex& index);
    void loadFromFile(const QString& fileName);
    void saveToFile(const QString& fileName);
};
//------------------------------------------------------------------------------
