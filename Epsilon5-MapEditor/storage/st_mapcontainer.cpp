#include "../utils/uexception.h"
#include "../utils/usettings.h"
#include "storage/st_mapcontainer.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
namespace containers {
//------------------------------------------------------------------------------
const char* DEFAULT_OBJECTS_FILE = "objects.txt";
const char* DEFAULT_RESPAWNS_FILE = "points.txt";
const char* DEFAULT_MAP_CONFIG_FILE = "config.ini";
const char* DEFAULT_MAP_BACKGROUND_FILE = "background.png";
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
TMapContainer::TMapContainer(QObject* parent)
    : QObject(parent)
    , TTContainer()
{
}
//------------------------------------------------------------------------------
TMapContainer::TMapItemId TMapContainer::addMap(const TMapItem& mapItem)
{
    return addItem(mapItem);
}
//------------------------------------------------------------------------------
void TMapContainer::removeMap(const TMapItem &mapItem)
{
    removeItem(mapItem);
}
//------------------------------------------------------------------------------
void TMapContainer::removeMap(TMapItemId id)
{
    removeItem(id);
}
//------------------------------------------------------------------------------
void TMapContainer::loadMapList(const QString& listFileName,
        const QDir& baseDirectory)
{
    QFile file(listFileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(listFileName));
    }
    QTextStream stream(&file);
    QDir dir(baseDirectory);
    QString line;
    while (!stream.atEnd()) {
        line = stream.readLine().trimmed();
        dir.setPath(baseDirectory.absolutePath() + "/" + line);
        if (!dir.exists()) {
            continue;
        }
        // Load map via loading map files (config, objects, points, ...)
        try {
            loadMapByName(dir.dirName());
        } catch (const UException& ex) {
            qDebug("%s", ex.what());
        }
    }
    file.close();
}
//------------------------------------------------------------------------------
void TMapContainer::loadMapByName(const QString& mapName,
        const QDir& baseDirectory)
{
    QDir mapDir(baseDirectory.absolutePath() + "/" + mapName);
    if (!mapDir.exists()) {
        throw UException(QString(Q_FUNC_INFO)
            .append(":: cannot open directory: '%1'").arg(mapDir.absolutePath()));
    }

    TObjectContainer objects;
    try {
        objects.loadObjectList(QString(mapDir.absolutePath())
                .append("/").append(DEFAULT_OBJECTS_FILE));
    } catch (const UException& ex) {
        qDebug("%s", ex.what());
    }

    TRespawnContainer respawns;
    try {
        respawns.loadRespawnList(QString(mapDir.absolutePath())
                .append("/").append(DEFAULT_RESPAWNS_FILE));
    } catch (const UException& ex) {
        qDebug("%s", ex.what());
    }

    TMapItem map(mapInfoFromFile(mapDir.absolutePath()
            .append("/").append(DEFAULT_MAP_CONFIG_FILE)),
            objects, respawns);

    map.setBackground(mapDir.absolutePath()
            .append("/").append(DEFAULT_MAP_BACKGROUND_FILE));
    map.setResourceFile(mapDir.absolutePath());
    addMap(map);
}
//------------------------------------------------------------------------------
void TMapContainer::saveMapByName(const QString& mapName, const QDir& baseDirectory)
{
    // TODO: implement this
}
//------------------------------------------------------------------------------
void TMapContainer::saveMapList(const QString& listFileName,
        const QDir& baseDirectory)
{
    QFile file(listFileName);
    if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(listFileName));
    }

    QDir mapDir(baseDirectory);
    QTextStream stream(&file);
    auto it = constBegin();
    for( ; it != constEnd(); ++it )
    {
        const TMapItem& map = *it;
        if (!map.isValid()) {
            continue;
        }

        // Create folder for map files
        mapDir.setPath(baseDirectory.absolutePath() + "/" + map.name());
        if (!mapDir.exists()) {
            mapDir.mkdir(map.name());
            mapDir.setPath(baseDirectory.absolutePath() + "/" + map.name());
        }
        // Save objects
        if (map.objects().count() > 0) {
            try {
                map.objects().saveObjectList(QString(mapDir.absolutePath())
                        .append("/").append(DEFAULT_OBJECTS_FILE));
            } catch (const UException& ex) {
                qDebug("%s", ex.what());
                continue;
            }
        }
        // Save respawns
        if (map.respawns().count() > 0) {
            try {
                map.respawns().saveRespawnList(QString(mapDir.absolutePath())
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
                          map.info());
        } catch (const UException& ex) {
            qDebug("%s", ex.what());
            continue;
        }
        // Append to list
        stream << map.name() << "\n";
    }
    file.close();
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
void TMapContainer::loadMap(const TMapItem &map)
{
    loadMapByName(map.name(), map.resourceFile());
}
//------------------------------------------------------------------------------
void TMapContainer::saveMap(const TMapItem &map)
{
    saveMapByName(map.name(), map.resourceFile());
}
//------------------------------------------------------------------------------
