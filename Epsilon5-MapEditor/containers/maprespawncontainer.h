// maprespawncontainer.h
#pragma once
#include "containers/structures.h"
#include "containers/container.h"
#include "containers/maprespawnitem.h"
//------------------------------------------------------------------------------
class TMapRespawnContainer : public TContainer
{
public:
    TMapRespawnContainer(QObject* parent = 0);
    TMapRespawnContainer(const TMapRespawnContainer& container);
    ~TMapRespawnContainer();
    void addRespawn(const TMapRespawnInfo& info);
    void removeRespawn(const QModelIndex& index);
    void loadFromFile(const QString& fileName);
    void saveToFile(const QString& fileName);
};
//------------------------------------------------------------------------------
