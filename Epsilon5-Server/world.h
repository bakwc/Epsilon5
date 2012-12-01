#pragma once

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QList>
#include <QSet>
#include <Box2D/Box2D.h>
#include <QDebug>

#include "player.h"
#include "bullet.h"
#include "staticobject.h"
#include "dynamicobject.h"

class QRect;
class TApplication;

class TWorld : public QObject, public b2ContactListener
{
    Q_OBJECT
public:
    typedef QList<TBullet*> TBulletsList;
    typedef QList<TStaticObject*> TStaticObjectsList;
    typedef QList<TDynamicObject*> TDynamicObjectsList;
    typedef QHash<size_t, TPlayer*> TPlayersHash;
public:
    TWorld(QObject *parent = 0);
    ~TWorld();
    void Start();
    inline b2World* GetB2World() {
        return B2World;
    }
    TPlayer* GetPlayer(size_t id);
    QByteArray Serialize();
public slots:
    void PlayerSpawn(size_t id);
    void PlayerKill(size_t id);
    void SpawnBullet(TBullet *bullet);
    void SpawnObject(size_t id, int x, int y, double angle);
    void SpawnBorders(const QSize &mapSize);
    void ClearObjects();
    void ClearBorders();
private:
    void timerEvent(QTimerEvent *);
    TApplication* Application();
    void spawnStaticObject(TStaticObjectsList &container, size_t id,
            double x, double y, const QSizeF& size, double angle = 0.0);
    void spawnDynamicObject(TDynamicObjectsList &container, size_t id,
            double x, double y, double vx, double vy,
            const QSizeF& size, double angle = 0.0);
    void BeginContact(b2Contact* contact);
private:
    b2World* B2World;
    TPlayersHash Players;
    TBulletsList Bullets;
    TStaticObjectsList StaticObjects;
    TDynamicObjectsList DynamicObjects;
    TStaticObjectsList WorldBorders;
};
