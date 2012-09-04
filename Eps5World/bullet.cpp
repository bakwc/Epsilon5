#include "bullet.h"

Bullet::Bullet(QObject *parent) :
    DynamicObject(parent)
{
    _ttl = 800; // TODO: Remove MN
}

void Bullet::applyPhysics()
{
    _ttl--;
    _x+=_vx;
    _y+=_vy;
    // TODO: Make physics
}
