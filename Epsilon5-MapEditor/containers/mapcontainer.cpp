#include <QStandardItem>
#include "stuctures.h"
#include "mapcontainer.h"
#include "mapobjectcontainer.h"
#include "maprespawncontainer.h"
//------------------------------------------------------------------------------
TMapItem::TMapItem()
    : QStandardItem()
    , mInfo(new TMapInfo)
    , mObjects(new TMapObjectContainer)
    , mRespawns(new TMapRespawnContainer)
{
}
//------------------------------------------------------------------------------
TMapContainer::TMapContainer(QObject* parent)
    : TContainer(parent)
{
}
//------------------------------------------------------------------------------
void TMapContainer::clear()
{
    mModel->clear();
}
//------------------------------------------------------------------------------
TMapContainer::TMapId TMapContainer::addMap(const TMapInfo& info, const QIcon& preview)
{
//    TMapItem* mapItem = new TMapItem;
//    QStandardItem* stdItem = new QStandardItem(preview, info.name);
//    mModel->appendRow(&stdItem);
}
//------------------------------------------------------------------------------
void TMapContainer::removeMap(TMapContainer::TMapId mapId)
{
}
//------------------------------------------------------------------------------
