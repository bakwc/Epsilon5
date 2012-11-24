#pragma once
#include "dynamicobject.h"

class TBullet : public TDynamicObject
{
    Q_OBJECT
public:
    TBullet(double x, double y, double vx, double vy, double d, QObject *parent = 0);
    void ApplyCustomPhysics();
    inline size_t GetTtl() {
        return Ttl;
    }
private:
    size_t Ttl;
};
