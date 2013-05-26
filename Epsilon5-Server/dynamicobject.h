#pragma once

#include <QObject>
#include <QDebug>
#include <QPointF>
#include <Box2D/Box2D.h>
#include "../Epsilon5-Proto/Epsilon5.pb.h"

struct TObjectInfo {
    enum EObjType {
        OT_Player,
        OT_Bullet,
        OT_Other
    };
    EObjType ObjType;
    void *Object;
};

struct TObjectParams {
    TObjectParams(QPointF position = QPointF(0, 0),
                  QPointF size = QPointF(0, 0),
                  QPointF speed = QPointF(0, 0),
                  double radius = 0)
        : Position(position)
        , Size(size)
        , Speed(speed)
        , Radius(radius)
    {
    }
    TObjectParams(double radius) {
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
    double Angle = 0;
    double Radius = 0;
    double Density = 0.6;
    double Friction = 0.8;
    double LinearDamping = 5.0;
    double AngularDamping = 2.9;
    size_t GroupIndex = 0;
    double Restitution = 0;
    bool IsBullet = false;
};

class TDynamicObject : public QObject
{
    Q_OBJECT
public:
    explicit TDynamicObject(const TObjectParams& params, QObject* parent);
    virtual ~TDynamicObject();
    // GetX, GetY, GetVx, GetVy now depricated; use GetPosition, GetSpeed
    inline double GetX() {
        return Body->GetPosition()(0);
    }
    inline double GetY() {
        return Body->GetPosition()(1);
    }
    inline double GetVx() {
        return Body->GetLinearVelocity()(0);
    }
    inline double GetVy() {
        return Body->GetLinearVelocity()(1);
    }
    inline double GetAngle() {
        return Body->GetAngle();
    }
    inline void setX(double x) {
        b2Vec2 pos = Body->GetPosition();
        pos(0) = x;
        Body->SetTransform(pos, Body->GetAngle());
    }
    inline void setY(double y) {
        b2Vec2 pos = Body->GetPosition();
        pos(1) = y;
        Body->SetTransform(pos, Body->GetAngle());
    }
    inline void setVx(double vx) {
        b2Vec2 speed = Body->GetLinearVelocity();
        speed(0) = vx;
        Body->SetLinearVelocity(speed);
    }
    inline void setVy(double vy) {
        b2Vec2 speed = Body->GetLinearVelocity();
        speed(1) = vy;
        Body->SetLinearVelocity(speed);
    }
    inline void setAngle(double angle) {
        Body->SetTransform(Body->GetPosition(), angle);
    }
    virtual void ApplyCustomPhysics() {}
    inline void SetId(size_t id) {
        Id = id;
    }
    inline size_t GetId() {
        return Id;
    }
    inline QPointF GetPosition() {
        QPointF pos;
        pos.setX(Body->GetPosition()(0));
        pos.setY(Body->GetPosition()(1));
        return pos;
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
protected:
    b2World* B2World();
protected:
    b2Body* Body;
    size_t Id = 0;
};
