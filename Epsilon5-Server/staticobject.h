#pragma once

#include <QObject>
#include <Box2D/Box2D.h>
#include "../Epslion5-Proto/Epsilon5.pb.h"

class TStaticObject : public QObject
{
    Q_OBJECT
public:
    explicit TStaticObject(double x, double y, double angle,QObject *parent = 0);
    virtual ~TStaticObject() {}
    void SetRectSize(double width, double height);
protected:
    b2World* B2World();
protected:
    b2Body* Body;
};
