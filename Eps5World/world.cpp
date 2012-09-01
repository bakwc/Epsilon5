/**
* @file
* Definition of World
*/
#include <QDebug>
#include <QString>
#include "../Eps5World/world.h"
#include "../Eps5Proto/Epsilon5.pb.h"

World::World(QObject *parent) :
    QObject(parent)
{
}

void World::start()
{
    startTimer(5); // TODO: Remove MN
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

void World::deSerialize(const QByteArray &data)
{
    // TODO: write deSerialization
    Epsilon5::World world;
    world.ParseFromArray(data.data(),data.size());
    for (int i=0;i!=world.players_size();i++)
    {
        const Epsilon5::Player &player = world.players(i);
        auto plr=_players.find(player.id());
        if (plr==_players.end())
            plr=_players.insert(player.id(),new Player(this));
        Player &newPlayer=*(plr.value());
        newPlayer.setId(player.id());
        newPlayer.setX(player.x());
        newPlayer.setY(player.y());
        newPlayer.setVx(player.vx());
        newPlayer.setVy(player.vy());
        newPlayer.setAngle(player.angle());
    }
}

void World::timerEvent(QTimerEvent *event)
{
    //TODO: Make physics
    for (auto i=_players.begin();i!=_players.end();i++)
    {
        i.value()->applyPhysics();
    }
}

void World::requestRedraw()
{
    DrawableObjects objects;
    for (auto i=_players.begin();i!=_players.end();i++)
    {
        DrawableObject tmp;
        tmp.x=i.value()->x();
        tmp.y=i.value()->y();
        tmp.angle=i.value()->angle();
        tmp.imageName="player";
        objects.push_back(tmp);
    }
    emit redraw(objects);
}
