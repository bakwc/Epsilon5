#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QPoint>
#include <QSize>

#include "defines.h"

#include "../Epsilon5-Proto/Epsilon5.pb.h"

enum EMapStatus {
    MS_NoMap,
    MS_Loading,
    MS_Ready
};

struct TRespPoint {
    int X, Y;
    int SpawnRadius, CaptureRadius;
    bool IsMain;
    bool IsCapturable;
    size_t CaptureTime;
    ETeam Team;
};

class TMaps : public QObject
{
    Q_OBJECT
public:
    explicit TMaps(QObject *parent = 0);
    void LoadNextMap();
    inline EMapStatus GetStatus() {
        return MapStatus;
    }
    QString GetCurrentMap();
    QSize GetMapSize();
    void SerialiseRespPoints(Epsilon5::World& world);
    inline QVector<TRespPoint>& GetRespPoints() {
        return RespPoints;
    }

    void LoadMaps();

    QPoint GetSpawnPosition(ETeam team);
signals:
    void SpawnObject(size_t id, int x, int y, qreal angle);
    void SpawnVehicle(size_t id, int x, int y, qreal angle);
    void SpawnBorders(const QSize& MapSize);
    void ClearObjects();
    void ClearBorders();
    void ClearVehicles();
    void MapLoaded();
private:
    void LoadConfig(const QString& fileName);
    void LoadObjects(const QString& fileName);
    void LoadVehicles(const QString& fileName);
    void LoadRespPoints(const QString& fileName);
private:
    QStringList MapFiles;
    int CurrentMap = -1;
    QSize MapSize;
    EMapStatus MapStatus = MS_NoMap;
    QVector<TRespPoint> RespPoints;
};
