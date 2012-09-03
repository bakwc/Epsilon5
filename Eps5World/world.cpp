/**
* @file
* Definition of World
*/
#include <QDebug>
#include <QString>
#include "../Eps5World/dynamicobject.h"
#include "../Eps5World/world.h"
#include "../Eps5Proto/Epsilon5.pb.h"

World::World(QObject *parent) :
    QObject(parent)
{
    _worldState = new Epsilon5::World;
}
World::~World()
{
    delete _worldState;
}

void World::start()
{
    startTimer(10); // TODO: Remove MN
}

void World::spawnPlayer(quint32 id)
{
    qDebug() << Q_FUNC_INFO;
    Player *player = new Player(this);
    player->setId(id);
    _players.insert(id,player);
}

Epsilon5::World *World::serialize()
{
    Epsilon5::World &world=*_worldState;
    world.clear_bullets();
    world.clear_players();
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

   /*
    for (QVector<Bullet*>::iterator i=_bullets.begin();i!=_bullets.end();i++)
    {
        Epsilon5::Bullet *bullet=world.add_bullets();
        Bullet *b=*i;
        quint32 x=i->damage();
        bullet->set_x(i->x());
        bullet->set_y(i->y());
        bullet->set_vx(i->vx());
        bullet->set_vy(i->vy());
        bullet->set_angle(i->angle());
    }*/
    //QByteArray result;
    //result.resize(world.ByteSize());
    //world.SerializeToArray(result.data(),result.size());
    return _worldState;
}

void World::deSerialize(const QByteArray &data)
{
    // TODO: write deSerialization
    Epsilon5::World world;
    world.ParseFromArray(data.data(),data.size());

    _selfId = world.playerid();

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
/*
    for (int i=0;i!=world.players_size();i++)
    {
        const Epsilon5::Bullet &bullet = world.bullets(i);

        _bullets.clear();

        auto bull=_bullets.push_back(new Bullet(this));
        Bullet &newBullet=*(bull.value());
        newBullet.setX(bull.x());
        newBullet.setY(bull.y());
        newBullet.setVx(bull.vx());
        newBullet.setVy(bull.vy());
        newBullet.setAngle(bull.angle());
    }
    */
    requestRedraw();
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
        if (i.value()->id() == _selfId)
            tmp.imageName="selfPlayer";
        else
            tmp.imageName="enemyPlayer";
        objects.push_back(tmp);
    }
    emit redraw(objects);
}

Player *World::getPlayer(quint32 id)
{
    auto playerIt = _players.find(id);
    if (playerIt == _players.end())
        return NULL;
    return playerIt.value();
}
