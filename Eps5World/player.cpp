/**
* @file
* Definition of Player
*/
#include "../Eps5World/player.h"

Player::Player(QObject *parent) :
    QObject(parent)
{
    _id=0;
    _x=0;
    _y=0;
    _vx=0;
    _vy=0;
    _angle=0;
}

void Player::applyPhysics()
{
    _x+=_vx;
    _y+=_vy;
    // TODO: Make physics
}

void Player::applyControl(const Epsilon5::Control &control)
{
    if (control.keystatus().keydown()) _vy=-0.8;
    else if (control.keystatus().keyup()) _vy=0.8;
    else _vy=0;

    if (control.keystatus().keyleft()) _vx=-0.8;
    else if (control.keystatus().keyright()) _vx=0.8;
    else _vx=0;
}
