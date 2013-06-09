#pragma once

#include <memory>
#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QList>
#include <QSet>
#include <Box2D/Box2D.h>
#include <QDebug>
#include <QTime>

#include "player.h"
#include "bullet.h"
#include "object.h"
#include "vehicle.h"
#include "defines.h"

class QRect;
class TApplication;

using namespace std;

class TWorld : public QObject, public b2ContactListener
{
    Q_OBJECT
public:
    typedef QList<TBullet*> TBulletsList;
    typedef QList<TObject*> TStaticObjectsList;
    typedef QList<TObject*> TDynamicObjectsList;
    typedef QHash<size_t, TPlayer*> TPlayersHash;
    typedef QList<TVehicleBase*> TVehiclesList;
    typedef QVector<QPair<qreal, TObject *> > TObjDistanceList;
public:
    TWorld(QObject *parent = 0);
    ~TWorld();
    void Start();
    inline b2World* GetB2World() {
        return B2World.get();
    }
    TPlayer* GetPlayer(size_t id);
    QByteArray Serialize(size_t playerId, bool needFullPacket = false);
    void SetPingForPlayer(size_t id, size_t packetNumber);
signals:
    void PlayerKilled(size_t killerId); // When a player killed, id of a killer
public slots:
    void PlayerSpawn(size_t id, ETeam team);
    void PlayerKill(size_t id); // When a player killed, id of dead player
    void SpawnBullet(TBullet *bullet);
    void SpawnObject(size_t id, int x, int y, qreal angle);
    void SpawnVehicle(size_t id, int x, int y, qreal angle);
    void SpawnBorders(const QSize &mapSize);
    void ClearObjects();
    void ClearBorders();
    void ClearVehicles();
    void NeedFullPacket();
    void PlayerEnteredVehicle(size_t id);
    void PlayerLeftVehicle(size_t id);
    void Boom(QPointF position, qreal radius, size_t playerId);
private:
    void timerEvent(QTimerEvent *);
    TApplication* Application();
    void spawnStaticObject(TStaticObjectsList &container, size_t id,
            qreal x, qreal y, const QSizeF& size, qreal angle = 0.0);
    void spawnDynamicObject(TDynamicObjectsList &container, size_t id,
            QPointF pos, QPointF speed,
            const QSizeF& size, qreal angle = 0.0);
    void BeginContact(b2Contact* contact);
    QPointF GetPlayerPos(size_t playerId);
    TVehicleBase* FindNearestVehicle(QPointF position);
    TObjDistanceList GetNearestObjects(QPointF position, qreal radius);
private:
    unique_ptr<b2World> B2World;
    TPlayersHash Players;
    TBulletsList Bullets;
    TStaticObjectsList StaticObjects;
    TDynamicObjectsList DynamicObjects;
    TVehiclesList Vehicles;
    TStaticObjectsList WorldBorders;
    size_t CurrentPacketNumber = 0;
    QHash<size_t, QTime> Times;
};
