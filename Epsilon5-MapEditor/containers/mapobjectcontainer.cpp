// mapobjectcontainer.cpp
#include "mapobjectcontainer.h"
//------------------------------------------------------------------------------
TMapObjectItem::TMapObjectItem()
    : mInfo( new TMapObjectInfo )
{
}
//------------------------------------------------------------------------------
TMapObjectItem::TMapObjectItem(TMapObjectInfo* objectInfo)
    : mInfo( objectInfo )
{
}
//------------------------------------------------------------------------------
TMapObjectItem::~TMapObjectItem()
{
    if( mInfo )
        delete mInfo;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
TMapObjectContainer::TMapObjectContainer(QObject* parent)
    : TContainer(parent)
{
}
//------------------------------------------------------------------------------
TMapObjectContainer::TMapObjectContainer(TMapObjectContainer* container,
        QObject* parent)
    : TContainer(parent)
{
}
//------------------------------------------------------------------------------
