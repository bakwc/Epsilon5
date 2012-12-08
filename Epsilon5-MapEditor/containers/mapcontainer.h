// mapcontainer.h
#pragma once
#include "containers/structures.h"
#include "containers/container.h"
#include "containers/mapitem.h"
#include "containers/mapobjectcontainer.h"
#include "containers/maprespawncontainer.h"
//------------------------------------------------------------------------------
namespace oldcontainers
{
//------------------------------------------------------------------------------
class TMapContainer : public TContainer
{
public:
    TMapContainer(QObject* parent = 0);
    TMapContainer(const TMapContainer& container);
    ~TMapContainer();

    void addMap(const TMapInfo& info,
                const TMapRespawnContainer& respawns);
    void addMap(const TMapInfo& info,
                const TMapObjectContainer& objects = TMapObjectContainer(),
                const TMapRespawnContainer& respawns = TMapRespawnContainer());
    void removeMap(const QModelIndex& index);
    void loadMapFromFile(const QString& mapName);
    void loadFromFile(const QString& fileName);
    void saveToFile(const QString& fileName);
    QStandardItemModel* objectModel(const QModelIndex& index) const;
    QStandardItemModel* respawnModel(const QModelIndex& index) const;
    void setBaseDirectory(const QString& directory);
    const QString& baseDirectory() const;
    TMapObjectContainer* objects(const QModelIndex& mapIndex);

    // Map settings function
    QString mapName(const QModelIndex& index) const;
    qint32 mapWidth(const QModelIndex& index) const;
    qint32 mapHeight(const QModelIndex& index) const;
    void setMapName(const QModelIndex& index, const QString& name);
    void setMapWidth(const QModelIndex& index, qint32 value);
    void setMapHeight(const QModelIndex& index, qint32 value);

    // Object settings function
//    qint32 objectX(const QModelIndex& mapIndex, const QModelIndex& index) const;
//    qint32 objectY(const QModelIndex& mapIndex, const QModelIndex& index) const;
//    qreal objectAngle(const QModelIndex& mapIndex, const QModelIndex& index) const;
//    quint32 objectId(const QModelIndex& mapIndex, const QModelIndex& index) const;
//    void setObjectX(const QModelIndex& mapIndex, const QModelIndex& index, qint32 x);
//    void setObjectY(const QModelIndex& mapIndex, const QModelIndex& index, qint32 y);
//    void setObjectAngle(const QModelIndex& mapIndex, const QModelIndex& index, qreal angle);
//    void setObjectId(const QModelIndex& mapIndex, const QModelIndex& index, quint32 id);

    // Respawn settings function

private:
    TMapInfo mapInfoFromFile(const QString& fileName);
    void mapInfoToFile(const QString& fileName, const TMapInfo& info);
    TMapItem mapItemFromIndex(const QModelIndex& index) const;
//    TMapObjectItem objectItemFromIndex(const QModelIndex& mapIndex,
//            const QModelIndex& index) const;

private:
    QString mBaseDirectory;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
