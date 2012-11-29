#include <QSize>
#include <QFile>
#include <QTextStream>
#include "../utils/uexception.h"
#include "../utils/usettings.h"
#include "maps.h"

TMaps::TMaps(QObject *parent)
    : QObject(parent)
    , MapStatus(MS_NoMap)
{
}

void TMaps::LoadMaplist(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UException("Error opening file " + fileName);
    }
    QTextStream in(&file);
    QString line = "";
    while (!line.isNull()) {
        line = in.readLine();
        if (line.isEmpty() || line[0] == '#') {
            continue;
        }
        MapFiles.push_back(line);
    }
    CurrentMap = -1;
    MapStatus = MS_NoMap;
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

    // TODO: Set return type from QPoint to QSize in GetMapSize()
    QPoint pt = GetMapSize();
    emit SpawnBorders(QSize(pt.x(),pt.y()));
    MapStatus = MS_Ready;
}

void TMaps::LoadConfig(const QString& fileName) {
    USettings conf;
    conf.Load(fileName);
    bool ok = true;
    MapSize.setX(conf.GetParameter("width").toInt(&ok));
    if (!ok) {
        throw UException("Error parsing " + fileName);
    }
    MapSize.setY(conf.GetParameter("height").toInt(&ok));
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
        bool ok = true;
        size_t id = objectParams[3].toInt(&ok);
        if (!ok) {
            throw UException("Error parsing " + fileName);
        }
        int x = objectParams[0].toInt(&ok);
        if (!ok) {
            throw UException("Error parsing " + fileName);
        }
        int y = objectParams[1].toInt(&ok);
        if (!ok) {
            throw UException("Error parsing " + fileName);
        }
        double angle = objectParams[2].toDouble(&ok);
        if (!ok) {
            throw UException("Error parsing " + fileName);
        }
        emit SpawnObject(id, x, y, angle);
    }
}

QString TMaps::GetCurrentMap() {
    if (CurrentMap == -1 || MapFiles.size() < CurrentMap) {
        throw UException("Map not initialised");
    }
    return MapFiles[CurrentMap];
}

QPoint TMaps::GetMapSize() {
    if (CurrentMap == -1 || MapFiles.size() < CurrentMap) {
        throw UException("Map not initialised");
    }
    return MapSize;
}
