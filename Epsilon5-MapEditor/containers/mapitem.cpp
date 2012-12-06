// mapitem.cpp
#include "containers/mapitem.h"
//------------------------------------------------------------------------------
TMapItem::TMapItem(QObject* parent)
    : QObject(parent)
    , mInfo(new TMapInfo)
    , mObjects(new TMapObjectContainer(this))
    , mRespawns(new TMapRespawnContainer(this))
    , mValid(false)
{
}
//------------------------------------------------------------------------------
TMapItem::TMapItem(const TMapItem& map)
    : QObject(map.parent())
    , mInfo(map.mInfo)
    , mObjects(new TMapObjectContainer(map.mObjects))
    , mRespawns(new TMapRespawnContainer(map.mRespawns))
    , mValid(map.mValid)
{
}
//------------------------------------------------------------------------------
TMapItem::TMapItem(const TMapInfo& mapInfo,
    const TMapObjectContainer& objectContainer,
    const TMapRespawnContainer& respawnContainer,
    QObject* parent)
    : QObject(parent)
    , mInfo(new TMapInfo(mapInfo))
    , mObjects(new TMapObjectContainer(objectContainer))
    , mRespawns(new TMapRespawnContainer(respawnContainer))
{
    mValid = checkData();
}
//------------------------------------------------------------------------------
TMapItem::~TMapItem()
{
}
//------------------------------------------------------------------------------
bool TMapItem::checkData()
{
    // TODO: Add map checking
    return !mInfo->name.isEmpty();
}
//------------------------------------------------------------------------------
bool TMapItem::isValid()
{
    return mValid = checkData();
}
//------------------------------------------------------------------------------
TMapInfo TMapItem::mapInfo() const
{
    return *mInfo;
}
//------------------------------------------------------------------------------
QString TMapItem::serialize()
{
    return mInfo->pack();
}
//------------------------------------------------------------------------------
