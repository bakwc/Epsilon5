// mapitem.cpp
#include "containers/mapitem.h"
//------------------------------------------------------------------------------
TMapItem::TMapItem()
    : QStandardItem()
    , mInfo(new TMapInfo)
    , mObjects(new TMapObjectContainer)
    , mRespawns(new TMapRespawnContainer)
{
}
//------------------------------------------------------------------------------
