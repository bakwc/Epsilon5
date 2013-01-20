#include <QDebug>
#include <cmath>
#include "../utils/uexception.h"
#include "dynamicobject.h"
#include "world.h"

TDynamicObject::TDynamicObject(QPointF pos, QPointF speed,
                               double angle, QObject *parent)
    : QObject(parent)
{
    if (std::isnan(x) || std::isnan(y)
            || std::isnan(vx) || std::isnan(vy) || std::isnan(angle))
    {
        throw UException(QString(Q_FUNC_INFO) + ": Value is NaN");
    }
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x(), pos.y());
    bodyDef.linearVelocity.Set(speed.x(), speed.y());
    bodyDef.angle = angle;
    Body = B2World()->CreateBody(&bodyDef);
    Body->SetLinearDamping(5.0);
    Body->SetAngularDamping(2.9);
}

b2World* TDynamicObject::B2World() {
    return ((TWorld*)(parent()))->GetB2World();
}

TDynamicObject::~TDynamicObject() {
    B2World()->DestroyBody(Body);
}

void TDynamicObject::SetRectSize(double width, double height) {
    b2PolygonShape polygon;
    polygon.SetAsBox(width / 2, height / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;
    fixtureDef.density = 0.6f;
    fixtureDef.friction = 0.8f;
    Body->CreateFixture(&fixtureDef);
}
