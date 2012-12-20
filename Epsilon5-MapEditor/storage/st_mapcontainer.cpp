#include "../utils/ucast.h"
#include "../utils/uexception.h"
#include "../utils/usettings.h"
#include "storage/st_mapcontainer.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
namespace containers
{
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
// Load maps from maplist file from baseDirectory by map's name
void TMapContainer::loadMapList(const QString& listFileName,
        const QDir& baseDirectory)
{
    QFile file(listFileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(listFileName));
    }

    clearItems();

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
            loadMapByName(dir.dirName(), baseDirectory.absolutePath());
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
    addItem(map);
}
//------------------------------------------------------------------------------
void TMapContainer::saveMap(const TMapItem& map, const QDir& baseDirectory)
{
    QString mapDirWithName = baseDirectory.absolutePath()
            .append("/").append(map.name());
    QDir mapDir(map.resourceFile());
    if( map.resourceFile().isEmpty() ) {
        mapDir.setPath(mapDirWithName);
    }

    qDebug() << mapDirWithName;
    qDebug() << "map objects:" << map.objects().count();
    qDebug() << "map respawns:" << map.respawns().count();

    // Create folder for map files
    if (!mapDir.exists()) {
        mapDir.mkdir(mapDirWithName);
        mapDir.setPath(mapDirWithName);
    }

    // Copy background
    QString mapBackground = mapDir.absolutePath()
            .append("/").append(DEFAULT_MAP_BACKGROUND_FILE);
    if(map.background() != mapBackground) {
        if( QFile::exists(mapBackground) ) {
            QFile::remove(mapBackground);
        }
        QFile::copy(map.background(), mapBackground);
    }

    // Save objects
    if (map.objects().count() > 0) {
        try {
            map.objects().saveObjectList(QString(mapDir.absolutePath())
                    .append("/").append(DEFAULT_OBJECTS_FILE));
        } catch (const UException& ex) {
            qDebug("%s", ex.what());
            return;
        }
    }

    // Save respawns
    if (map.respawns().count() > 0) {
        try {
            map.respawns().saveRespawnList(QString(mapDir.absolutePath())
                    .append("/").append(DEFAULT_RESPAWNS_FILE));
        } catch (const UException& ex) {
            qDebug("%s", ex.what());
            return;
        }
    }

    // Save config
    try {
        mapInfoToFile(QString(mapDir.absolutePath())
                      .append("/").append(DEFAULT_MAP_CONFIG_FILE),
                      map.info());
    } catch (const UException& ex) {
        qDebug("%s", ex.what());
    }
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

    QTextStream stream(&file);
    auto it = constBegin();
    for (; it != constEnd(); ++it) {
        const TMapItem& map = (*it);
        if (!map.isValid()) {
            qDebug("Not valid map '%s'", qPrintable(map.name()));
            continue;
        }

        saveMap(map, baseDirectory);
        if( map.resourceFile().isEmpty() )
            stream << map.name() << "\n";
        else
            stream << QDir(map.resourceFile()).dirName() << "\n";
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
    params["color"] = "";
    try {
        settings.DefineParams(params);
        settings.Load(fileName,
            QStringList() << "name" << "width" << "height" << "color");
    } catch (USettings& ex) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: illegal map config detected in '%1'").arg(fileName));
    }
    TMapInfo info;
    QString name = settings.GetParameter("name");
    info.name = name;
    info.width = settings.GetParameter("width");
    info.height = settings.GetParameter("height");
    info.color = (const QColor&)settings.GetParameter("color");
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
    params["color"] = QVariant(info.color).toString();
    try {
        settings.DefineParams(params);
        settings.Save(fileName);
    } catch (USettings& ex) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: illegal map config detected in '%1'").arg(fileName));
    }
}
//------------------------------------------------------------------------------
void TMapContainer::loadMap(const TMapItem& map)
{
    loadMapByName(map.name(), map.resourceFile());
}
//------------------------------------------------------------------------------
void TMapContainer::deleteMap(const TMapItem& mapItem)
{
    // TODO: inmplement this
    Q_UNUSED(mapItem)
}
//------------------------------------------------------------------------------
