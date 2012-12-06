// mapobjectitem.cpp
#include "mapobjectitem.h"
//------------------------------------------------------------------------------
TMapObjectItem::TMapObjectItem(QObject* parent)
    : QObject(parent)
    , mInfo(new TMapObjectInfo)
    , mValid(false)
{
}
//------------------------------------------------------------------------------
TMapObjectItem::TMapObjectItem(const TMapObjectItem &object)
    : QObject(object.parent())
    , mInfo(object.mInfo)
    , mValid(object.mValid)
{
}
//------------------------------------------------------------------------------
TMapObjectItem::TMapObjectItem(const TMapObjectInfo& objectInfo, QObject* parent)
    : QObject(parent)
    , mInfo(new TMapObjectInfo(objectInfo))
{
    mValid = checkData();
}
//------------------------------------------------------------------------------
TMapObjectItem::~TMapObjectItem()
{
}
//------------------------------------------------------------------------------
bool TMapObjectItem::checkData()
{
    return true;
}
//------------------------------------------------------------------------------
bool TMapObjectItem::isValid()
{
    return mValid = checkData();
}
//------------------------------------------------------------------------------
TMapObjectInfo TMapObjectItem::objectInfo() const
{
    return *mInfo;
}
//------------------------------------------------------------------------------
QString TMapObjectItem::serialize()
{
    return mInfo->pack();
}
//------------------------------------------------------------------------------
