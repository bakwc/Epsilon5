// maprespawnitem.cpp
#include "containers/maprespawnitem.h"
//------------------------------------------------------------------------------
TMapRespawnItem::TMapRespawnItem(QObject* parent)
    : QObject(parent)
    , mInfo(new TMapRespawnInfo)
    , mValid(false)
{
}
//------------------------------------------------------------------------------
TMapRespawnItem::TMapRespawnItem(const TMapRespawnItem& respawn)
    : QObject(respawn.parent())
    , mInfo(respawn.mInfo)
    , mValid(respawn.mValid)
{
}
//------------------------------------------------------------------------------
TMapRespawnItem::TMapRespawnItem(const TMapRespawnInfo& respawnInfo,
        QObject* parent)
    : QObject(parent)
    , mInfo(new TMapRespawnInfo(respawnInfo))
{
    mValid = checkData();
}
//------------------------------------------------------------------------------
TMapRespawnItem::~TMapRespawnItem()
{
}
//------------------------------------------------------------------------------
bool TMapRespawnItem::checkData()
{
    return true;
}
//------------------------------------------------------------------------------
bool TMapRespawnItem::isValid()
{
    return mValid = checkData();
}
//------------------------------------------------------------------------------
bool TMapRespawnItem::isValid() const
{
    return mValid;
}
//------------------------------------------------------------------------------
TMapRespawnInfo TMapRespawnItem::respawnInfo() const
{
    return *mInfo;
}
//------------------------------------------------------------------------------
QString TMapRespawnItem::serialize() const
{
    return mInfo->pack();
}
//------------------------------------------------------------------------------
