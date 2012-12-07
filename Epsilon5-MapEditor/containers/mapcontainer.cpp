// mapcontainer.cpp
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "../utils/uexception.h"
#include "../utils/usettings.h"
#include "containers/mapcontainer.h"
//------------------------------------------------------------------------------
const char* DEFAULT_OBJECTS_FILE = "objects.txt";
const char* DEFAULT_RESPAWNS_FILE = "points.txt";
const char* DEFAULT_MAP_CONFIG_FILE = "config.ini";
const char* DEFAULT_BASE_DIRECTORY = "./";
//------------------------------------------------------------------------------
TMapContainer::TMapContainer(QObject* parent)
    : TContainer(parent)
    , mBaseDirectory(QString(DEFAULT_BASE_DIRECTORY))
{
}
//------------------------------------------------------------------------------
TMapContainer::TMapContainer(const TMapContainer& container)
    : TContainer(container)
    , mBaseDirectory(QString(DEFAULT_BASE_DIRECTORY))
{
}
//------------------------------------------------------------------------------
TMapContainer::~TMapContainer()
{
}
//------------------------------------------------------------------------------
void TMapContainer::addMap(const TMapInfo& info,
        const TMapRespawnContainer& respawns)
{
    addMap(info, TMapObjectContainer(), respawns);
}
//------------------------------------------------------------------------------
void TMapContainer::addMap(const TMapInfo& info,
        const TMapObjectContainer& objects,
        const TMapRespawnContainer& respawns)
{
    TMapItem* map = new TMapItem(info, objects, respawns);
    QStandardItem* item = new QStandardItem;
    item->setData(QVariant::fromValue(*map));
    item->setText(map->serialize());
    item->setEditable(false);
    mModel->appendRow(item);
    ++mLastValidId;
}
//------------------------------------------------------------------------------
void TMapContainer::removeMap(const QModelIndex& index)
{
    mModel->removeRow(index.row());
}
//------------------------------------------------------------------------------
// Load maplist from file
// Each line is a map directory name. The folder BASE_MAP_DIR/MAP_DIR_NAME
// must exists
void TMapContainer::loadFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(fileName));
    }
    QTextStream stream(&file);
    QDir dir(mBaseDirectory);
    QString line;
    while (!stream.atEnd()) {
        line = stream.readLine().trimmed();
        dir.setPath(mBaseDirectory + "/" + line);
        if (!dir.exists()) {
            continue;
        }
        // Load map via loading map files (config, objects, points, ...)
        try {
            loadMapFromFile(dir.dirName());
        } catch (const UException& ex) {
            qDebug("%s", ex.what());
        }
    }
    file.close();
}
//------------------------------------------------------------------------------
void TMapContainer::loadMapFromFile(const QString& mapName)
{
    QDir mapDir(mBaseDirectory + "/" + mapName);
    if (!mapDir.exists()) {
        return;
    }
    TMapObjectContainer objects;
    try {
        objects.loadFromFile(QString(mapDir.absolutePath())
                .append("/").append(DEFAULT_OBJECTS_FILE));
    } catch (const UException& ex) {
        qDebug("%s", ex.what());
    }
    TMapRespawnContainer respawns;
    try {
        respawns.loadFromFile(QString(mapDir.absolutePath())
                .append("/").append(DEFAULT_RESPAWNS_FILE));
    } catch (const UException& ex) {
        qDebug("%s", ex.what());
    }
    addMap(mapInfoFromFile(QString(mapDir.absolutePath()
            .append("/").append(DEFAULT_MAP_CONFIG_FILE))),
            objects, respawns);
}
//------------------------------------------------------------------------------
TMapInfo TMapContainer::mapInfoFromFile(const QString& fileName)
{
    USettings settings;
    USettings::TParametersHash params;
    params["name"] = "";
    params["width"] = "";
    params["height"] = "";
    try {
        settings.LoadDefaults(params);
        settings.Load(fileName, QStringList() << "name" << "width" << "height");
    } catch (USettings& ex) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: illegal map config detected in '%1'").arg(fileName));
    }
    TMapInfo info;
    QString name = settings.GetParameter("name");
    info.name = name;
    info.width = settings.GetParameter("width");
    info.height = settings.GetParameter("height");
    return info;
}
//------------------------------------------------------------------------------
void TMapContainer::mapInfoToFile(const QString& fileName, const TMapInfo& info)
{
    USettings settings;
    USettings::TParametersHash params;
    params["name"] = info.name;
    params["width"] = QString().number(info.width);
    params["height"] = QString().number(info.height);
    try {
        settings.LoadDefaults(params);
        settings.Save(fileName);
    } catch (USettings& ex) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: illegal map config detected in '%1'").arg(fileName));
    }
}
//------------------------------------------------------------------------------
// Save maplist to file
void TMapContainer::saveToFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(fileName));
    }
    QDir mapDir(mBaseDirectory);
    QTextStream stream(&file);
    for (int i = 0; i < mModel->rowCount(); ++i) {
        const TMapItem& map = mModel->item(i)->data().value<TMapItem>();
        if (!map.isValid()) {
            continue;
        }
        mapDir.setPath(mBaseDirectory + "/" + map.mapInfo()->name);
        if (!mapDir.exists()) {
            mapDir.mkdir(map.mapInfo()->name);
            mapDir.setPath(mBaseDirectory + "/" + map.mapInfo()->name);
        }
        // Save objects
        if (map.objects()->count() > 0) {
            try {
                map.objects()->saveToFile(QString(mapDir.absolutePath())
                        .append("/").append(DEFAULT_OBJECTS_FILE));
            } catch (const UException& ex) {
                qDebug("%s", ex.what());
                continue;
            }
        }
        // Save respawns
        if (map.respawns()->count() > 0) {
            try {
                map.respawns()->saveToFile(QString(mapDir.absolutePath())
                        .append("/").append(DEFAULT_RESPAWNS_FILE));
            } catch (const UException& ex) {
                qDebug("%s", ex.what());
                continue;
            }
        }
        // Save config
        try {
            mapInfoToFile(QString(mapDir.absolutePath())
                          .append("/").append(DEFAULT_MAP_CONFIG_FILE),
                          *map.mapInfo());
        } catch (const UException& ex) {
            qDebug("%s", ex.what());
            continue;
        }
        // Append to list
        stream << map.mapInfo()->name << "\n";
    }
    file.close();
}
//------------------------------------------------------------------------------
QStandardItemModel* TMapContainer::objectModel(const QModelIndex& index) const
{
    const QStandardItem* item = mModel->itemFromIndex(index);
    return item->data().value<TMapItem>().objects()->model();
}
//------------------------------------------------------------------------------
QStandardItemModel* TMapContainer::respawnModel(const QModelIndex& index) const
{
    const QStandardItem* item = mModel->itemFromIndex(index);
    return item->data().value<TMapItem>().respawns()->model();
}
//------------------------------------------------------------------------------
void TMapContainer::setBaseDirectory(const QString& directory)
{
    QDir dir(directory);
    if (!dir.exists()) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: base directory not exists"));
        return;
    }
    mBaseDirectory = directory;
}
//------------------------------------------------------------------------------
const QString& TMapContainer::baseDirectory() const
{
    return mBaseDirectory;
}
//------------------------------------------------------------------------------
TMapItem TMapContainer::mapItemFromIndex(const QModelIndex &index) const
{
    const QStandardItem* item = mModel->itemFromIndex(index);
    return item->data().value<TMapItem>();
}
//TMapObjectItem TMapContainer::objectItemFromIndex(const QModelIndex& mapIndex,
//        const QModelIndex& index) const
//{
//    const QStandardItem* item = mModel->itemFromIndex(mapIndex);
//    TMapItem mapItem = item->data().value<TMapItem>();
//    return mapItem.objects();
//}
//------------------------------------------------------------------------------
QString TMapContainer::mapName(const QModelIndex &index) const
{
    return mapItemFromIndex(index).mapInfo()->name;
}
//------------------------------------------------------------------------------
qint32 TMapContainer::mapWidth(const QModelIndex &index) const
{
    return mapItemFromIndex(index).mapInfo()->width;
}
//------------------------------------------------------------------------------
qint32 TMapContainer::mapHeight(const QModelIndex &index) const
{
    return mapItemFromIndex(index).mapInfo()->height;
}
//------------------------------------------------------------------------------
void TMapContainer::setMapName(const QModelIndex &index, const QString &name)
{
    QStandardItem* item = mModel->itemFromIndex(index);
    const TMapItem& mapItem = item->data().value<TMapItem>();
    mapItem.mapInfo()->name = name;
    item->setData(QVariant::fromValue(mapItem));
    item->setText(mapItem.mapInfo()->pack());
}
//------------------------------------------------------------------------------
void TMapContainer::setMapWidth(const QModelIndex &index, qint32 value)
{
    QStandardItem* item = mModel->itemFromIndex(index);
    const TMapItem& mapItem = item->data().value<TMapItem>();
    mapItem.mapInfo()->width = value;
    item->setData(QVariant::fromValue(mapItem));
    item->setText(mapItem.mapInfo()->pack());
}
//------------------------------------------------------------------------------
void TMapContainer::setMapHeight(const QModelIndex &index, qint32 value)
{
    QStandardItem* item = mModel->itemFromIndex(index);
    const TMapItem& mapItem = item->data().value<TMapItem>();
    mapItem.mapInfo()->height = value;
    item->setData(QVariant::fromValue(mapItem));
    item->setText(mapItem.mapInfo()->pack());
}
//------------------------------------------------------------------------------
TMapObjectContainer* TMapContainer::objects(const QModelIndex &mapIndex)
{
    QStandardItem* item = mModel->itemFromIndex(mapIndex);
    const TMapItem& mapItem = item->data().value<TMapItem>();
    return mapItem.objects();
}
//------------------------------------------------------------------------------
//qint32 objectX(const QModelIndex& mapIndex, const QModelIndex& index) const
//{
//}
////------------------------------------------------------------------------------
//qint32 TMapContainer::objectY(const QModelIndex& mapIndex,
//        const QModelIndex& index) const
//{
//}
////------------------------------------------------------------------------------
//qreal TMapContainer::objectAngle(const QModelIndex& mapIndex,
//        const QModelIndex& index) const
//{
//}
////------------------------------------------------------------------------------
//quint32 TMapContainer::objectId(const QModelIndex& mapIndex,
//        const QModelIndex& index) const
//{
//}
////------------------------------------------------------------------------------
//void TMapContainer::setObjectX(const QModelIndex& mapIndex,
//        const QModelIndex& index, qint32 x)
//{
//}
////------------------------------------------------------------------------------
//void TMapContainer::setObjectY(const QModelIndex& mapIndex,
//        const QModelIndex& index, qint32 y)
//{
//}
////------------------------------------------------------------------------------
//void TMapContainer::setObjectAngle(const QModelIndex& mapIndex,
//        const QModelIndex& index, qreal angle)
//{
//}
////------------------------------------------------------------------------------
//void sTMapContainer::etObjectId(const QModelIndex& mapIndex,
//        const QModelIndex& index, quint32 id)
//{
//}
//------------------------------------------------------------------------------
