#include "storage/st_respawncontainer.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
TRespawnContainer::TRespawnContainer(QObject* parent)
    : QObject(parent)
    , TTContainer()
{
}
//------------------------------------------------------------------------------
TRespawnContainer::TRespawnContainer(const TRespawnContainer& container)
    : QObject(container.parent())
    , TTContainer(container)
{
}
//------------------------------------------------------------------------------
TRespawnContainer& TRespawnContainer::operator =(const TRespawnContainer& container)
{
    TTContainer::operator =(container);
    return *this;
}
//------------------------------------------------------------------------------
