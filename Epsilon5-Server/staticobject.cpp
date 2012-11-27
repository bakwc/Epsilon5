#include <QVector>
#include "staticobject.h"
#include "world.h"

TStaticObject::TStaticObject(double x, double y, double angle, QObject *parent)
    : QObject(parent)
    , Id(0)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);
    bodyDef.angle = angle;
    Body = B2World()->CreateBody(&bodyDef);
}

b2World* TStaticObject::B2World() {
    return ((TWorld*)(parent()))->GetB2World();
}

void TStaticObject::SetRectSize(double width, double height) {
    b2PolygonShape polygon;
    polygon.SetAsBox(width / 2, height / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;
    Body->CreateFixture(&fixtureDef);
}
