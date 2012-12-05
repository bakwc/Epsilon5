#include "respawnscontainer.h"
//------------------------------------------------------------------------------
TMapRespawnItem::TMapRespawnItem()
    : mInfo( new TMapRespawnInfo )
{
}
//------------------------------------------------------------------------------
TMapRespawnItem::TMapRespawnItem(TMapRespawnInfo* respawnInfo)
    : mInfo( respawnInfo )
{
}
//------------------------------------------------------------------------------
TMapRespawnItem::~TMapRespawnItem()
{
    if( mInfo )
        delete mInfo;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
TMapRespawnContainer::TMapRespawnContainer(QObject* parent)
    : TContainer(parent)
{
}
//------------------------------------------------------------------------------
