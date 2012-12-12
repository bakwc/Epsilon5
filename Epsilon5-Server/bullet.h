#pragma once
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "dynamicobject.h"

class TBullet : public TDynamicObject
{
    Q_OBJECT
public:
    TBullet(double x, double y, double vx, double vy,
            Epsilon5::Bullet_Type bulletType, size_t playerId, QObject *parent = 0);
    void ApplyCustomPhysics();
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
private:
    size_t Ttl;
    TObjectInfo CollisionInfo;
    Epsilon5::Bullet_Type BulletType;
    size_t PlayerId;
};
