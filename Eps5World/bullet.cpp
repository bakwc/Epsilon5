#include "bullet.h"

Bullet::Bullet(QObject *parent) :
    DynamicObject(parent)
{
}

void Bullet::applyPhysics()
{
    _x+=_vx;
    _y+=_vy;
    // TODO: Make physics
}
