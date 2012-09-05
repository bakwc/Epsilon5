#include "bullet.h"
#include <QDebug>

Bullet::Bullet(QObject *parent) :
    DynamicObject(parent)
{
    _ttl = 800; // TODO: Remove MN
}

void Bullet::applyPhysics()
{
    _ttl--;
    DynamicObject::_x+=DynamicObject::_vx;
    DynamicObject::_y+=DynamicObject::_vy;
    // TODO: Make physics
}
