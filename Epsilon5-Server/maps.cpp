#include <QFile>
#include <QTextStream>
#include "../utils/uexception.h"
#include "../utils/usettings.h"
#include "../utils/ucast.h"
#include "../utils/ucolonsep.h"
#include "maps.h"
#include <QDir>

#include <QDebug>

const int X_OFFSET = 100;
const int Y_OFFSET = 200;
const int MAP_SCALE = 100;

TMaps::TMaps(QObject *parent)
    : QObject(parent)
{
}

void TMaps::LoadMaps()
{
    QDir dir("maps");
    QStringList entryList = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

    if (entryList.isEmpty())
        throw UException("Cannot find maps files in " + dir.canonicalPath());

    MapFiles << entryList;
}

void TMaps::LoadNextMap() {
    MapStatus = MS_Loading;
    if (MapFiles.size() == 0) {
        throw UException("No maps found");
    }
    CurrentMap ++;
    if (CurrentMap >= MapFiles.size()) {
        CurrentMap = 0;
    }
    emit ClearObjects();
    emit ClearBorders();
    emit ClearVehicles();
    emit ClearTerrains();

    QString configDir = "maps/" + MapFiles[CurrentMap];
    LoadConfig(configDir + "/config.ini");
    LoadObjects(configDir + "/objects.txt");
    LoadVehicles(configDir + "/vehicles.txt");
    LoadRespPoints(configDir + "/points.txt");
    LoadTerrains(configDir + "/terrains.txt");

    emit SpawnBorders(GetMapSize());
    MapStatus = MS_Ready;
    emit MapLoaded();
}

void TMaps::LoadConfig(const QString& fileName) {
    USettings conf;
    conf.Load(fileName);
    bool ok = true;
    MapSize.setWidth(conf.GetParameter("width"));
    if (!ok) {
        throw UException("Error parsing " + fileName);
    }
    MapSize.setHeight(conf.GetParameter("height"));
    if (!ok) {
        throw UException("Error parsing " + fileName);
    }
}

void TMaps::LoadObjects(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UException("Error opening " + fileName);
    }
    QTextStream in(&file);
    QString line = "";
    while (!line.isNull()) {
        line = in.readLine();
        if (line.isEmpty() || line[0] == '#') {
            continue;
        }
        QStringList objectParams = line.split(":");
        if (objectParams.size() != 4) {
            throw UException("Error parsing " + fileName);
        }

        int id = FromString(objectParams[3]);
        int x = FromString(objectParams[0]);
        int y = FromString(objectParams[1]);
        qreal angle = FromString(objectParams[2]);

        emit SpawnObject(id, x, y, angle);
    }
}

void TMaps::LoadVehicles(const QString &fileName) {
    UColonSep sep;
    sep.Load(fileName);

    for (size_t i = 0; i < sep.Rows(); i++) {
        try {
        int x,y;
        qreal angle;
        int id;

        x = sep.Get(i, 0);
        y = sep.Get(i, 1);
        angle = sep.Get(i, 2);
        id = sep.Get(i, 3);

        emit SpawnVehicle(id, x, y, angle);
        } catch (const UException& e) {
            qDebug() << "Problems with loading: " << fileName;
        }
    }
}


void TMaps::LoadRespPoints(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UException("Error opening " + fileName);
    }
    QTextStream in(&file);
    QString line = "";
    while (!line.isNull()) {
        line = in.readLine();
        if (line.isEmpty() || line[0] == '#') {
            continue;
        }
        QStringList params = line.split(":");
        if (params.size() != 8) {
            throw UException("Error parsing " + fileName);
        }

        TRespPoint point;

        //x:y:capture_radius:spawn_radius:is_capturable:is_main:capture_time:team
        point.X = FromString(params[0]);
        point.Y = FromString(params[1]);
        point.CaptureRadius = FromString(params[2]);
        point.SpawnRadius = FromString(params[3]);
        point.IsCapturable = FromString(params[4]);
        point.IsMain = FromString(params[5]);
        point.CaptureTime = FromString(params[6]);
        point.Team = FromString(params[7]) ? T_One : T_Second;
        RespPoints.push_back(point);
    }
}

ETerrain ToTerrainType(const QString str)
{
  if (str == "water") return T_Water;
  if (str == "dirt") return T_Dirt;
  else throw UException("Unknown terrain requested");
}

void TMaps::LoadTerrains(const QString &fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      throw UException("Error opening " + fileName);
  }
  QTextStream in(&file);
  QString line = "";

  while ((line = in.readLine()) != "%%") {
    if (line.isEmpty() || line[0] == '#') {
      continue;
    }
    QStringList size = line.split(":");
  }

  line = "";
  while ((line = in.readLine()) != "%%") {
    if (line.isEmpty() || line[0] == '#') {
      continue;
    }
    QStringList defs = line.split(":");
    ETerrain terrain = ToTerrainType(defs[1]);
    TerrainIds.insert(defs[0], terrain);
    TerrainFrictions[terrain] = defs[2].toDouble();
  }

  line = "";
  while (!in.atEnd()) {
    line = in.readLine();
    if (line.isEmpty() || line[0] == '#') {
      continue;
    }
    QStringList row = line.split(":");
    assert(row.size() == MapSize.width() / MAP_SCALE);
    for (const QString& id : row)
      TerrainAreas.append(TerrainIds[id]);
  }
}

QString TMaps::GetCurrentMap() {
    if (CurrentMap == -1 || MapFiles.size() < CurrentMap) {
        throw UException("Map not initialised");
    }
    return MapFiles[CurrentMap];
}

QSize TMaps::GetMapSize() {
    if (CurrentMap == -1 || MapFiles.size() < CurrentMap) {
        throw UException("Map not initialised");
    }
    return MapSize;
}

void TMaps::SerialiseRespPoints(Epsilon5::World& world) {
    for (auto i = RespPoints.begin(); i != RespPoints.end(); i++) {
        auto point = world.add_resp_points();
        point->set_x(i->X);
        point->set_y(i->Y);
        point->set_is_main(i->IsMain);
        point->set_team(i->Team);
    }
}
QPoint translateToTopLeft(const QPointF& position)
{
  int x = position.x() + X_OFFSET;
  int y = position.y() + Y_OFFSET;
  return QPoint(x, y);
}

double TMaps::GetFrictionByPos(const QPointF &position) const
{
  QPoint newPos = translateToTopLeft(position);
  size_t x = newPos.x() / 10;
  size_t y = newPos.y() / 10;
  size_t index = y * MapSize.width() / MAP_SCALE + x;
  qDebug() << index;

  return TerrainFrictions[TerrainAreas[index]];
}

QPoint TMaps::GetSpawnPosition(ETeam team) {
    QVector<TRespPoint*> matchPoints;
    for (auto i = RespPoints.begin(); i != RespPoints.end(); i++) {
        if (i->Team == team) {
            matchPoints.push_back(&(*i));
        }
    }
    if (matchPoints.size() == 0) {
        throw UException("No resp points available!");
    }
    int n = rand()%(matchPoints.size());

    int x, y, sr;
    x = matchPoints[n]->X;
    y = matchPoints[n]->Y;
    sr = matchPoints[n]->SpawnRadius;

    QPoint res;
    res.setX(x - sr / 2 + rand() % (sr + 1));
    res.setY(y - sr / 2 + rand() % (sr + 1));
    return res;
}
