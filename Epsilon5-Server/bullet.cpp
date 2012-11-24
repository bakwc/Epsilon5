#include "bullet.h"

/*
TBullet::TBullet(double x, double y, double vx, double vy, QObject *parent)
    : TDynamicObject(0, 0, 0, 0, 0, parent)
{
    b2CircleShape circle;
    circle.m_p.Set(GetX(), GetY());
    circle.m_radius = 0.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 0.8f;
    fixtureDef.filter.groupIndex = 1;
    Body->CreateFixture(&fixtureDef);

    Ttl = 3000;
}
*/

TBullet::TBullet(double x, double y, double vx, double vy, double d, QObject *parent)
    : TDynamicObject(x, y, vx, vy, 0, parent)
    //: TDynamicObject(0, 0, 0, 0, 0, parent)
{
    b2CircleShape circle;
    circle.m_p.Set(0, 0);
    circle.m_radius = 0.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 0.8f;
    fixtureDef.filter.groupIndex = 1;
    Body->CreateFixture(&fixtureDef);

    Ttl = 3000;
}

void TBullet::ApplyCustomPhysics() {
    b2Vec2 force(0, 0.1);
    Body->ApplyForceToCenter(force);
    Ttl--;
}
