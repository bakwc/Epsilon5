/**
* @file
* Definition of Player
*/
#include "../Eps5World/player.h"
#include <cmath>

const float PI=3.1415926f;

Player::Player(QObject *parent) :
    DynamicObject(parent)
{
    _id=0;
    _circle.m_p.Set(DynamicObject::_x, DynamicObject::_y);
    _circle.m_radius = 15f;
}

void Player::applyPhysics()
{
    DynamicObject::_x+=DynamicObject::_vx;
    DynamicObject::_y+=DynamicObject::_vy;
    // TODO: Make physics
}

void Player::applyControl(const Epsilon5::Control &control)
{
    if (control.keystatus().keydown()) DynamicObject::_vy=-0.8;
    else if (control.keystatus().keyup()) DynamicObject::_vy=0.8;
    else DynamicObject::_vy=0;

    if (control.keystatus().keyleft()) DynamicObject::_vx=-0.8;
    else if (control.keystatus().keyright()) DynamicObject::_vx=0.8;
    else DynamicObject::_vx=0;

    if (control.keystatus().keyattack1())   // FIRE!!
    {
        Bullet *bullet = new Bullet(this);
        bullet->setX(this->x());
        bullet->setY(this->y());
        bullet->setVx(2.8*sin(angle()+PI/2));
        bullet->setVy(2.8*cos(angle()+PI/2));
        emit spawnBullet(bullet);
    }

    DynamicObject::_angle=control.angle();
}
