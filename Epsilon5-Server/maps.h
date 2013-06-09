#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QPoint>
#include <QSize>
#include <QMap>

#include "defines.h"

#include "../Epsilon5-Proto/Epsilon5.pb.h"

//! Possible terrain zones on map
enum ETerrain {
  T_Dirt,
  T_Water,
  T_Space
};

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

    double GetFrictionByPos(const QPointF &position) const;

    void LoadMaps();

    QPoint GetSpawnPosition(ETeam team);
signals:
    void SpawnObject(size_t id, int x, int y, qreal angle);
    void SpawnVehicle(size_t id, int x, int y, qreal angle);
    void SpawnBorders(const QSize& MapSize);
    void ClearObjects();
    void ClearBorders();
    void ClearVehicles();
    void ClearTerrains();
    void MapLoaded();
private:
    void LoadConfig(const QString& fileName);
    void LoadObjects(const QString& fileName);
    void LoadVehicles(const QString& fileName);
    void LoadRespPoints(const QString& fileName);
    void LoadTerrains(const QString& fileName);
private:
    QStringList MapFiles;
    int CurrentMap = -1;
    QSize MapSize;
    EMapStatus MapStatus = MS_NoMap;
    QVector<TRespPoint> RespPoints;

    QVector<ETerrain> TerrainAreas; //!< Массив зон для всей карты,
    QMap<QString, ETerrain> TerrainIds; //!< Идентификаторы зон
    QMap<ETerrain, double> TerrainFrictions; //!< Набор Зон и соответствующих сил трения
};
