// mapobjectitem.cpp
#include "mapobjectitem.h"
//------------------------------------------------------------------------------
TMapObjectItem::TMapObjectItem()
    : mInfo(new TMapObjectInfo)
{
}
//------------------------------------------------------------------------------
TMapObjectItem::TMapObjectItem(TMapObjectInfo* objectInfo)
    : mInfo(objectInfo)
{
}
//------------------------------------------------------------------------------
TMapObjectItem::~TMapObjectItem()
{
    if (mInfo) {
        delete mInfo;
    }
}
//------------------------------------------------------------------------------
