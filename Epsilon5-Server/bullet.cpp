#include "bullet.h"

TBullet::TBullet(double x, double y, double vx, double vy,
                 Epsilon5::Bullet_Type bulletType, QObject *parent)
    : TDynamicObject(x, y, vx, vy, 0, parent)
    , BulletType(bulletType)
{
    b2FixtureDef fixtureDef;
    b2CircleShape circle;

    switch(bulletType) {
    case Epsilon5::Bullet_Type_ARBUZ: {
        circle.m_p.Set(0, 0);
        circle.m_radius = 0.5f;
        fixtureDef.shape = &circle;
        fixtureDef.density = 1.0f;
    } break;
    case Epsilon5::Bullet_Type_LITTLE_BULLET: {
        circle.m_p.Set(0, 0);
        circle.m_radius = 0.3f;
        fixtureDef.shape = &circle;
        fixtureDef.density = 3.0f;
    } break;
    default:
        break;
    }

    fixtureDef.friction = 0.1f;
    fixtureDef.restitution = 0.5f;
    fixtureDef.filter.groupIndex = 1;
    Body->CreateFixture(&fixtureDef);

    Body->SetLinearDamping(0.0);
    Body->SetAngularDamping(0.3);

    Body->SetUserData(&CollisionInfo);
    CollisionInfo.ObjType = TObjectInfo::OT_Bullet;
    CollisionInfo.Object = this;

    Ttl = 300;
}

void TBullet::ApplyCustomPhysics() {
    b2Vec2 force(0, 0.1);
    Body->ApplyForceToCenter(force);
    if (Ttl > 0) {
        Ttl--;
    }
}
