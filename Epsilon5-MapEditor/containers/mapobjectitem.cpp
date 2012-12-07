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
TMapObjectItem::TMapObjectItem(const TMapObjectInfo& objectInfo, QObject* parent)
    : QObject(parent)
    , mInfo(new TMapObjectInfo(objectInfo))
{
    mValid = checkData();
}
//------------------------------------------------------------------------------
TMapObjectItem::TMapObjectItem(const TMapObjectItem& object)
    : QObject(object.parent())
    , mInfo(new TMapObjectInfo(*object.mInfo))
    , mValid(object.mValid)
{
}
//------------------------------------------------------------------------------
TMapObjectItem::~TMapObjectItem()
{
}
//------------------------------------------------------------------------------
TMapObjectItem& TMapObjectItem::operator =(const TMapObjectItem& object)
{
    mInfo = new TMapObjectInfo(*object.mInfo);
    mValid = object.mValid;
    return *this;
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
bool TMapObjectItem::isValid() const
{
    return mValid;
}
//------------------------------------------------------------------------------
TMapObjectInfo TMapObjectItem::objectInfo() const
{
    return *mInfo;
}
//------------------------------------------------------------------------------
QString TMapObjectItem::serialize() const
{
    return mInfo->pack();
}
//------------------------------------------------------------------------------
