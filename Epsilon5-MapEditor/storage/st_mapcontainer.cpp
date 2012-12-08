#include "storage/st_mapcontainer.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
TMapContainer::TMapContainer(QObject* parent)
    : QObject(parent)
    , TTContainer()
{
}
//------------------------------------------------------------------------------
quint32 TMapContainer::addMap(const TMapItem& mapItem)
{
    return addItem(mapItem);
}
//------------------------------------------------------------------------------
