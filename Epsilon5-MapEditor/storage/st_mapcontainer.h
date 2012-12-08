#pragma once
#include <QObject>
#include "storage/container_t.h"
#include "storage/st_storageinfo.h"
#include "storage/st_mapitem.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
class TMapContainer : public QObject, public TTContainer<TMapItem>
{
    Q_OBJECT
public:
    typedef TMapItem::TItemId TMapItemId;

public:
    explicit TMapContainer(QObject* parent = 0);
    TMapItemId addMap(const TMapItem& mapItem);
    void removeMap(const TMapItem& mapItem);
    void removeMap(TMapItemId id);

    void loadMapByName(const QString& mapName,
            const QDir& baseDirectory = QDir::currentPath());
    void saveMapByName(const QString& mapName,
            const QDir& baseDirectory = QDir::currentPath());
    void loadMapList(const QString& listFileName,
            const QDir& baseDirectory = QDir::currentPath());
    void saveMapList(const QString& listFileName,
            const QDir& baseDirectory = QDir::currentPath());

    void loadMap(const TMapItem& map);
    void saveMap(const TMapItem& map);

private:
    TMapInfo mapInfoFromFile(const QString& fileName);
    void mapInfoToFile(const QString& fileName, const TMapInfo& info);
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
