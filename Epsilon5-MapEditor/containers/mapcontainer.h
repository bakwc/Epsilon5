// mapscontainer.h
#pragma once
#include <QStandardItem>
#include "object.h"
#include "objectcontainer.h"
#include "respawncontainer.h"
#include "container.h"
//------------------------------------------------------------------------------
//class USettings;
//class TMapInfo;
//class TMapObjectContainer;
//class TMapRespawnContainer;
//------------------------------------------------------------------------------
class TMapItem : public QStandardItem
{
    Q_OBJECT
public:
    TMapItem();
//    TMapItem(TMapInfo* mapInfo);
//    TMapItem(TMapInfo* mapInfo, TMapObjectContainer* objects,
//            TMapRespawnContainer* respawns);

private:
    TMapInfo* mInfo;
    TMapObjectContainer* mObjects;
    TMapRespawnContainer* mRespawns;
};
//------------------------------------------------------------------------------
class TMapContainer : public TContainer
{
public:
    typedef quint32 TMapId;

public:
    TMapContainer(QObject* parent = 0);
    void clear();
    TMapId addMap( const TMapInfo& info, const QIcon& preview );
    void removeMap( TMapId mapId );

    const TMapObjectContainer* objects(TMapId mapId) const;
    TMapObjectContainer* objects(TMapId mapId);

private:
};
//------------------------------------------------------------------------------
