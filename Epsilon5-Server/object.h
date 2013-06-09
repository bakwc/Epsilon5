#pragma once

#include <QObject>
#include <QDebug>
#include <QPointF>
#include <Box2D/Box2D.h>
#include "../Epsilon5-Proto/Epsilon5.pb.h"

enum EObjectType {
    OT_Undefined,
    OT_Player,
    OT_Static,
    OT_Dynamic,
    OT_Bullet,
    OT_Vehicle
};

struct TObjectParams {
    TObjectParams(QPointF position = QPointF(0, 0),
                  QPointF size = QPointF(0, 0),
                  QPointF speed = QPointF(0, 0),
                  qreal radius = 0)
        : Position(position)
        , Size(size)
        , Speed(speed)
        , Radius(radius)
    {
    }
    TObjectParams(qreal radius) {
        Position.setX(0);
        Position.setY(0);
        Speed.setX(0);
        Speed.setY(0);
        Size.setX(0);
        Size.setY(0);
        Radius = radius;
    }
    QPointF Position;
    QPointF Size;
    QPointF Speed;
    qreal Angle = 0;
    qreal Radius = 0;
    qreal Density = 0.6;
    qreal Friction = 0.8;
    qreal LinearDamping = 5.0;
    qreal AngularDamping = 2.9;
    size_t GroupIndex = 0;
    qreal Restitution = 0;
    bool IsBullet = false;
    bool IsDynamic = true;
    size_t TypeId = 0;
    EObjectType Type = OT_Undefined;
};

class TObject : public QObject
{
    Q_OBJECT
public:
    explicit TObject(const TObjectParams& params, QObject* parent);
    virtual ~TObject();
    // GetX, GetY, GetVx, GetVy now depricated; use GetPosition, GetSpeed
    inline qreal GetX() {
        return Body->GetPosition()(0);
    }
    inline qreal GetY() {
        return Body->GetPosition()(1);
    }
    inline qreal GetVx() {
        return Body->GetLinearVelocity()(0);
    }
    inline qreal GetVy() {
        return Body->GetLinearVelocity()(1);
    }
    inline qreal GetAngle() {
        return Body->GetAngle();
    }
    inline void setX(qreal x) {
        b2Vec2 pos = Body->GetPosition();
        pos(0) = x;
        Body->SetTransform(pos, Body->GetAngle());
    }
    inline void setY(qreal y) {
        b2Vec2 pos = Body->GetPosition();
        pos(1) = y;
        Body->SetTransform(pos, Body->GetAngle());
    }
    inline void setVx(qreal vx) {
        b2Vec2 speed = Body->GetLinearVelocity();
        speed(0) = vx;
        Body->SetLinearVelocity(speed);
    }
    inline void setVy(qreal vy) {
        b2Vec2 speed = Body->GetLinearVelocity();
        speed(1) = vy;
        Body->SetLinearVelocity(speed);
    }
    inline void setAngle(qreal angle) {
        Body->SetTransform(Body->GetPosition(), angle);
    }
    virtual void ApplyCustomPhysics() {}
    /*inline void SetId(size_t id) {
        Id = id;
    }
    inline size_t GetId() {
        return Id;
    }*/
    inline QPointF GetPosition() {
        QPointF pos;
        pos.setX(Body->GetPosition()(0));
        pos.setY(Body->GetPosition()(1));
        return pos;
    }
    inline void SetPosition(const QPointF& position) {
        b2Vec2 pos(position.x(), position.y());
        Body->SetTransform(pos, Body->GetAngle());;
    }
    inline QPointF GetSpeed() {
        QPointF pos;
        pos.setX(Body->GetLinearVelocity()(0));
        pos.setY(Body->GetLinearVelocity()(1));
        return pos;
    }
    inline void Activate() {
        Body->SetActive(true);
    }
    inline void DeActivate() {
        Body->SetActive(false);
    }
    inline bool IsActive() {
        return Body->IsActive();
    }
    inline void ApplyImpulse(QPointF impulse) {
        b2Vec2 impulseVec(impulse.x(), impulse.y());
        Body->ApplyLinearImpulse(impulseVec, Body->GetPosition());
    }
    virtual void ApplyDamage(qreal, size_t) {
    }
    inline bool IsDynamic() {
        return Body->GetType() == b2_dynamicBody;
    }
    inline EObjectType GetType() {
        return ObjectType;
    }
    inline size_t GetTypeId() {
        return TypeId;
    }
    inline qreal GetRadius() {
        return Radius;
    }
protected:
    b2World* B2World();
protected:
    b2Body* Body;
//    size_t Id = 0;
    EObjectType ObjectType = OT_Undefined;
    /*  TypeId - concrete subtype of object, e. g.
      if ObjectType == OT_Static or OT_Dynamic, subtypes described
      in objects.txt file */
    size_t TypeId = 0;
    qreal Radius;
};
