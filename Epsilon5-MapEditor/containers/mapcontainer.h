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
    void addMap(const TMapInfo& info,
            const TMapRespawnContainer& respawns);
    void addMap(const TMapInfo &info,
            const TMapObjectContainer& objects = TMapObjectContainer(),
            const TMapRespawnContainer& respawns = TMapRespawnContainer());
    void removeMap(const QModelIndex& index);
    void loadMapFromFile(const QString& mapName);
    void loadFromFile(const QString& fileName);
    void saveToFile(const QString& fileName);
    QStandardItemModel* objectModel(const QModelIndex &index) const;
    QStandardItemModel* respawnModel(const QModelIndex &index) const;
    void setBaseDirectory(const QString& directory);
    const QString& baseDirectory() const;

private:
    TMapInfo mapInfoFromFile(const QString& fileName);
    void mapInfoToFile(const QString& fileName, const TMapInfo& info);

private:
    QString mBaseDirectory;
};
//------------------------------------------------------------------------------
