// mapcontainer.h
#pragma once
#include "containers/structures.h"
#include "containers/container.h"
#include "containers/mapitem.h"
#include "containers/mapobjectcontainer.h"
#include "containers/maprespawncontainer.h"
//------------------------------------------------------------------------------
class TMapContainer : public TContainer
{
public:
    TMapContainer(QObject* parent = 0);
    TMapContainer(const TMapContainer& container);
    ~TMapContainer();
    void addMap(const TMapInfo& info);
    void removeMap(const QModelIndex& index);
    void loadFromFile(const QString& fileName);
    void saveToFile(const QString& fileName);
};
//------------------------------------------------------------------------------
