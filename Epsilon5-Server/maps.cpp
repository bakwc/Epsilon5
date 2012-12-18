#include <QFile>
#include <QTextStream>
#include "../utils/uexception.h"
#include "../utils/usettings.h"
#include "../utils/ucast.h"
#include "maps.h"
#include <QDir>

#include <QDebug>

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
    LoadConfig("maps/" + MapFiles[CurrentMap] + "/config.ini");
    LoadObjects("maps/" + MapFiles[CurrentMap] + "/objects.txt");
    LoadRespPoints("maps/" + MapFiles[CurrentMap] + "/points.txt");
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
        double angle = FromString(objectParams[2]);

        emit SpawnObject(id, x, y, angle);
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
    res.setX(x - sr / 2 + rand() % sr);
    res.setY(y - sr / 2 + rand() % sr);
    return res;
}
