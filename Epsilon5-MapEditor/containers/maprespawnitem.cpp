// maprespawnitem.cpp
#include "containers/maprespawnitem.h"
//------------------------------------------------------------------------------
using namespace oldcontainers;
//------------------------------------------------------------------------------
TMapRespawnItem::TMapRespawnItem(QObject* parent)
    : QObject(parent)
    , mInfo(new TMapRespawnInfo)
    , mValid(false)
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
TMapRespawnItem::TMapRespawnItem(const TMapRespawnItem& respawn)
    : QObject(respawn.parent())
    , mInfo(new TMapRespawnInfo(*respawn.mInfo))
    , mValid(respawn.mValid)
{
}
//------------------------------------------------------------------------------
TMapRespawnItem::~TMapRespawnItem()
{
}
//------------------------------------------------------------------------------
TMapRespawnItem& TMapRespawnItem::operator =(const TMapRespawnItem& respawn)
{
    mInfo = new TMapRespawnInfo(*respawn.mInfo);
    mValid = respawn.mValid;
    return *this;
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
