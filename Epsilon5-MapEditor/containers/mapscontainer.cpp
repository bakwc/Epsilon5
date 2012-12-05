//#include <QFile>
//#include <QTextStream>
//#include "../utils/usettings.h"
#include <QStandardItem>
#include "object.h"
#include "mapscontainer.h"
#include "objectscontainer.h"
#include "respawnscontainer.h"
//------------------------------------------------------------------------------
//TMapContainer::TMapContainer(QObject* parent)
//    : TContainer(parent)
//    , mConfig(new USettings(this))
//{
//    USettings::TParametersHash defaulParams;
//    defaulParams["name"] = "Unknown";
//    defaulParams["width"] = "";
//    defaulParams["height"] = "";
//    mConfig->LoadDefaults(defaulParams);
//}
//------------------------------------------------------------------------------
//void TMapsContainer::loadFromFile(const QString& fileName)
//{
//    mConfig->Load(fileName, QStringList() << "name" << "width" << "height");
//}
//------------------------------------------------------------------------------
//void TMapsContainer::saveToFile(const QString& fileName)
//{
//    mConfig->Save(fileName);
//}
//------------------------------------------------------------------------------
TMapItem::TMapItem()
    : QStandardItem()
    , mInfo(new TMapInfo)
    , mObjects(new TMapObjectContainer)
    , mRespawns(new TMapRespawnContainer)
{
}
//------------------------------------------------------------------------------
//TMapItem::TMapItem(TMapInfo* mapInfo)
//    : mInfo(&mapInfo)
//    , mObjects(new TMapObjectContainer(this))
//    , mRespawns(new TMapRespawnContainer(this))
//{
//}
////------------------------------------------------------------------------------
//TMapItem::TMapItem(const TMapInfo& mapInfo, const TMapObjectContainer& objects,
//        const TMapRespawnContainer& respawns)
//    : mInfo(mapInfo)
//    , mObjects(objects)
//    , mRespawns(respawns)
//{
//}
//------------------------------------------------------------------------------
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
    TMapItem* mapItem = new TMapItem;
    //QStandardItem* stdItem = new QStandardItem(preview, info.name);
//    mModel->appendRow(&stdItem);
}
//------------------------------------------------------------------------------
void TMapContainer::removeMap(TMapContainer::TMapId mapId)
{

}
//------------------------------------------------------------------------------
