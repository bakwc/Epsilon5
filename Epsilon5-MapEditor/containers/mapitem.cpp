// mapitem.cpp
#include "containers/mapitem.h"
//------------------------------------------------------------------------------
using namespace oldcontainers;
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
TMapItem::TMapItem(const TMapItem& map)
    : QObject(map.parent())
    , mInfo(map.mInfo)
    , mObjects(map.mObjects)
    , mRespawns(map.mRespawns)
    , mValid(map.mValid)
{
}
//------------------------------------------------------------------------------
TMapItem::~TMapItem()
{
}
//------------------------------------------------------------------------------
TMapItem& TMapItem::operator =(const TMapItem& map)
{
    mInfo = new TMapInfo(*map.mInfo);
    mObjects = new TMapObjectContainer(map.mObjects);
    mRespawns = new TMapRespawnContainer(map.mRespawns);
    return *this;
}
//------------------------------------------------------------------------------
bool TMapItem::checkData() const
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
bool TMapItem::isValid() const
{
    return mValid;
}
//------------------------------------------------------------------------------
TMapInfo* TMapItem::mapInfo() const
{
    return mInfo;
}
//------------------------------------------------------------------------------
QString TMapItem::serialize() const
{
    return mInfo->pack();
}
//------------------------------------------------------------------------------
TMapObjectContainer* TMapItem::objects() const
{
    return mObjects;
}
//------------------------------------------------------------------------------
TMapRespawnContainer* TMapItem::respawns() const
{
    return mRespawns;
}
//------------------------------------------------------------------------------
