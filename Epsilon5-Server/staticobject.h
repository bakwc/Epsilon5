#pragma once

#include <QObject>
#include <Box2D/Box2D.h>
#include "../Epsilon5-Proto/Epsilon5.pb.h"

class TStaticObject : public QObject
{
    Q_OBJECT
public:
    explicit TStaticObject(double x, double y, double angle,QObject *parent = 0);
    virtual ~TStaticObject();
    void SetRectSize(double width, double height);
    inline double GetX() {
        return Body->GetPosition()(0);
    }
    inline double GetY() {
        return Body->GetPosition()(1);
    }
    inline double GetAngle() {
        return Body->GetAngle();
    }
    inline void SetId(size_t id) {
        Id = id;
    }
    inline size_t GetId() {
        return Id;
    }
protected:
    b2World* B2World();
protected:
    b2Body* Body;
    size_t Id;
};
