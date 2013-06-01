#include "../utils/uexception.h"

#include "defines.h"
#include "bullet.h"

TBullet::TBullet(const TObjectParams& params,
                 Epsilon5::Bullet_Type bulletType,
                 size_t playerId,
                 ETeam team,
                 QObject *parent)
    : TDynamicObject(params, parent)
    , BulletType(bulletType)
    , PlayerId(playerId)
    , Team(team)
{
    Body->SetUserData(&CollisionInfo);
    CollisionInfo.ObjType = TObjectInfo::OT_Bullet;
    CollisionInfo.Object = this;
    Ttl = 120;
}

void TBullet::ApplyCustomPhysics() {
    b2Vec2 force(0, 0.1);
    Body->ApplyForceToCenter(force);
    if (Ttl > 0) {
        Ttl--;
    }
}


TBullet *CreateBullet(QPointF pos, QPointF speed,
                      Epsilon5::Bullet_Type bulletType,
                      size_t playerId, ETeam team, QObject *parent)
{
    TObjectParams params;

    params.Friction = 0.1;
    params.Restitution = 0.5;
    params.GroupIndex = 1;
    params.IsBullet = true;
    params.LinearDamping = 0.0;
    params.AngularDamping = 0.3;
    params.Position = pos;
    params.Speed = speed;

    switch(bulletType) {
        case Epsilon5::Bullet_Type_ARBUZ: {
            params.Radius = 0.5;
            params.Density = 1.0;
            return new TBullet(params, bulletType, playerId, team, parent);
        } break;
        case Epsilon5::Bullet_Type_LITTLE_BULLET: {
            params.Radius = 0.3;
            params.Density = 3.0;
            return new TBullet(params, bulletType, playerId, team, parent);
        } break;
        case Epsilon5::Bullet_Type_GRENADE: {
            params.Radius = 0.5;
            params.Density = 1.0;
            return new TGrenadeBullet(params, bulletType, playerId, team, parent);
            break;
        }
    }

    throw UException("Unknown bullet type");
    return nullptr;
}

void TGrenadeBullet::OnDestroy() {
    emit Boom(GetPosition(), 15);
}

TGrenadeBullet::TGrenadeBullet(const TObjectParams &params,
                               Epsilon5::Bullet_Type bulletType,
                               size_t playerId, ETeam team,
                               QObject *parent)
    : TBullet(params, bulletType, playerId, team, parent)
{
    Ttl = 10;
    connect(this, &TGrenadeBullet::Boom, GWorld, &TWorld::Boom);
}
