#include "dynamicobject.h"
#include "world.h"

TDynamicObject::TDynamicObject(double x, double y, double vx,
                               double vy, double angle, QObject *parent)
    : QObject(parent)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    bodyDef.linearVelocity.Set(vx, vy);
    bodyDef.angle = angle;
    Body = B2World()->CreateBody(&bodyDef);
}

b2World* TDynamicObject::B2World() {
    return ((TWorld*)(parent()))->GetB2World();
}

TDynamicObject::~TDynamicObject() {
    B2World()->DestroyBody(Body);
}
