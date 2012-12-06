// mapitem.h
#pragma once
#include <QObject>
#include "containers/structures.h"
#include "containers/mapobjectcontainer.h"
#include "containers/maprespawncontainer.h"
//------------------------------------------------------------------------------
class TMapItem : public QObject
{
    Q_OBJECT
public:
    TMapItem(QObject* parent = 0);
    TMapItem(const TMapItem& map);
    TMapItem(const TMapInfo& mapInfo,
             const TMapObjectContainer& objectContainer = TMapObjectContainer(),
             const TMapRespawnContainer& respawnContainer = TMapRespawnContainer(),
             QObject* parent = 0);
    ~TMapItem();
    TMapInfo mapInfo() const;
    QString serialize() const;
    bool isValid();
    bool isValid() const;
    TMapObjectContainer* objects() const;
    TMapRespawnContainer* respawns() const;

private:
    bool checkData() const;

private:
    TMapInfo* mInfo;
    TMapObjectContainer* mObjects;
    TMapRespawnContainer* mRespawns;
    bool mValid;
};
//------------------------------------------------------------------------------
Q_DECLARE_METATYPE(TMapItem)
//------------------------------------------------------------------------------
