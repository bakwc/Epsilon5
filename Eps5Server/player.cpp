#include "player.h"

Player::Player(QObject *parent) :
    QObject(parent)
{
}

void Player::setId(quint32 id)
{
    _id=id;
}
