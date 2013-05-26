#include <QDebug>
#include <cmath>
#include "../utils/uexception.h"
#include "dynamicobject.h"
#include "world.h"

TDynamicObject::TDynamicObject(const TObjectParams& params, QObject* parent)
    : QObject(parent)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(params.Position.x(), params.Position.y());
    bodyDef.linearVelocity.Set(params.Speed.x(), params.Speed.y());
    bodyDef.angle = params.Angle;
    Body = B2World()->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    b2CircleShape circle;
    b2PolygonShape polygon;

    if (params.Radius != 0) {
        circle.m_p.Set(0, 0);
        circle.m_radius = params.Radius;
        fixtureDef.shape = &circle;
    } else if (params.Size.x() != 0 && params.Size.y() != 0) {
        polygon.SetAsBox(params.Size.x() / 2, params.Size.y() / 2);
        fixtureDef.shape = &polygon;
    } else {
        throw UException("Radius and size not specified!");
    }
    fixtureDef.density = params.Density;
    fixtureDef.friction = params.Friction;
    fixtureDef.filter.groupIndex = params.GroupIndex;
    Body->CreateFixture(&fixtureDef);

    Body->SetLinearDamping(params.LinearDamping);
    Body->SetAngularDamping(params.AngularDamping);
    Body->SetBullet(params.IsBullet);
}

b2World* TDynamicObject::B2World() {
    return ((TWorld*)(parent()))->GetB2World();
}

TDynamicObject::~TDynamicObject() {
    B2World()->DestroyBody(Body);
}
