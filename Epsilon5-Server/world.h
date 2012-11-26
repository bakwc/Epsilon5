#pragma once

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QList>
#include <Box2D/Box2D.h>
#include <QDebug>

#include "player.h"
#include "bullet.h"
#include "staticobject.h"
#include "dynamicobject.h"

class TWorld : public QObject
{
    Q_OBJECT
public:
    TWorld(QObject *parent = 0);
    void Start();
    inline b2World* GetB2World() {
        return B2World;
    }
    TPlayer* GetPlayer(size_t id);
    QByteArray Serialize();
public slots:
    void PlayerEnter(size_t id);
    void PlayerExit(size_t id);
    void SpawnBullet(TBullet *bullet);
    void SpawnObject(size_t id, int x, int y, double angle);
    void ClearObjects();
private:
    void timerEvent(QTimerEvent *);
private:
    b2World* B2World;
    QHash<size_t, TPlayer*> Players;
    QList<TBullet*> Bullets;
    QList<TStaticObject*> StaticObjects;
    QList<TDynamicObject*> DynamicObjects;
};
