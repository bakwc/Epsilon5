#include <QVector>
#include "../utils/uexception.h"
#include "staticobject.h"
#include "world.h"

TStaticObject::TStaticObject(double x, double y, double angle, QObject *parent)
    : QObject(parent)
    , Id(0)
{
    if (std::isnan(x) || std::isnan(y) || std::isnan(angle)) {
        throw UException("Value is NaN");
    }
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);
    bodyDef.angle = angle;
    Body = B2World()->CreateBody(&bodyDef);
}

TStaticObject::~TStaticObject() {
    B2World()->DestroyBody(Body);
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
