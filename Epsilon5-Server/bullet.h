#pragma once
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "dynamicobject.h"
#include "maps.h"

class TBullet : public TDynamicObject
{
    Q_OBJECT
public:
    TBullet(const TObjectParams& params,
            Epsilon5::Bullet_Type bulletType,
            size_t playerId, ETeam team,
            QObject *parent = 0);
    virtual void ApplyCustomPhysics();
    virtual void OnDestroy() {
    }
    inline size_t GetTtl() {
        return Ttl;
    }
    inline void Destroy() {
        Ttl = 0;
    }
    inline Epsilon5::Bullet_Type GetType() {
        return BulletType;
    }
    inline size_t GetPlayerId() {
        return PlayerId;
    }
    inline ETeam GetTeam() {
        return Team;
    }
    inline bool GetTeamBool() {
        return Team == T_One;
    }
protected:
    size_t Ttl;
    TObjectInfo CollisionInfo;
    Epsilon5::Bullet_Type BulletType;
    size_t PlayerId;
    ETeam Team;
};


class TGrenadeBullet : public TBullet
{
    Q_OBJECT
public:
    TGrenadeBullet(const TObjectParams& params,
                   Epsilon5::Bullet_Type bulletType,
                   size_t playerId, ETeam team,
                   QObject *parent = 0);
    void OnDestroy();
signals:
    void Boom(QPointF position, float radius);
};

TBullet* CreateBullet(QPointF pos, QPointF speed,
                      Epsilon5::Bullet_Type bulletType,
                      size_t playerId, ETeam team,
                      QObject *parent = 0);
