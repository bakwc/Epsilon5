/**
* @file
* Definition of World
*/
#include <QDebug>
#include "world.h"
#include "../Eps5Proto/Epsilon5.pb.h"

World::World(QObject *parent) :
    QObject(parent)
{
}

void World::start()
{
    startTimer(500); // TODO: Remove MN
}

void World::spawnPlayer(quint32 id)
{
    qDebug() << Q_FUNC_INFO;
    Player *player = new Player(this);
    player->setId(id);
    _players.insert(id,player);
}

QByteArray World::serialize()
{
    Epsilon5::World world;
    for (auto i=_players.begin();i!=_players.end();i++)
    {
        Epsilon5::Player *player=world.add_players();
        player->set_id(i.key());
        player->set_x(i.value()->x());
        player->set_y(i.value()->y());
        player->set_vx(i.value()->vx());
        player->set_vy(i.value()->vy());
        player->set_angle(i.value()->angle());
    }
    QByteArray result;
    result.resize(world.ByteSize());
    world.SerializeToArray(result.data(),result.size());
    return result;
}

void World::timerEvent(QTimerEvent *event)
{
    //TODO: Make physics
}
