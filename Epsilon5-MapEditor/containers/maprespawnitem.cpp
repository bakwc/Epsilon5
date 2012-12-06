// maprespawnitem.cpp
#include "maprespawnitem.h"
//------------------------------------------------------------------------------
//TMapRespawnItem::TMapRespawnItem()
TMapRespawnItem::TMapRespawnItem(QObject* parent)
    : QObject(parent)
    , mInfo(new TMapRespawnInfo)
    , mValid(false)
{
}
//------------------------------------------------------------------------------
TMapRespawnItem::TMapRespawnItem(const TMapRespawnInfo& respawnInfo)
//TMapRespawnItem::TMapRespawnItem(const TMapRespawnInfo& respawnInfo, QObject* parent)
//    : QObject(parent)
    : mInfo(new TMapRespawnInfo(respawnInfo))
{
    mValid = checkData();
}
//------------------------------------------------------------------------------
TMapRespawnItem::~TMapRespawnItem()
{
    if (mInfo) {
        delete mInfo;
    }
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
TMapRespawnInfo TMapRespawnItem::respawnInfo() const
{
    return *mInfo;
}
//------------------------------------------------------------------------------
QString TMapRespawnItem::serialize()
{
    return mInfo->pack();
}
