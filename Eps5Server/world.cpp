#include "world.h"

World::World(QObject *parent) :
    QObject(parent)
{
}

void World::spawnPlayer(quint32 id)
{
    Player *player = new Player(this);
    player->setId(id);
    _players.insert(id,player);
}
