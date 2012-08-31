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

void Player::setId(quint32 id)
{
    _id=id;
}
