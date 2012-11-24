#include <QDebug>
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include "world.h"

TWorld::TWorld(QObject *parent)
    : QObject(parent)
    , B2World(new b2World(b2Vec2(0, 0)))
{
}

TPlayer* TWorld::GetPlayer(size_t id) {
    if (Players.find(id) != Players.end()) {
        return Players[id];
    }
    // throw exception here!
    return 0;
}

QByteArray TWorld::Serialize() {
    Epsilon5::World world;
    world.clear_bullets();
    world.clear_players();

    for (auto i = Players.begin(); i != Players.end(); i++)
    {
        auto player = world.add_players();
        player->set_id(i.key());
        player->set_x(i.value()->GetX() * 10);
        player->set_y(i.value()->GetY() * 10);
        player->set_vx(i.value()->GetVx() * 10);
        player->set_vy(i.value()->GetVy() * 10);
        player->set_angle(i.value()->GetAngle());
        QByteArray playerName = i.value()->GetNickname().toLocal8Bit();
        player->set_name(playerName.data(), playerName.size());
    }

    for (auto i = Bullets.begin(); i != Bullets.end();i++)
    {
        auto bullet=world.add_bullets();
        bullet->set_x((*i)->GetX() * 10);
        bullet->set_y((*i)->GetY() * 10);
        bullet->set_vx((*i)->GetVx() * 10);
        bullet->set_vy((*i)->GetVy() * 10);
    }

    QByteArray result;
    result.resize(world.ByteSize());
    world.SerializeToArray(result.data(), result.size());
    return result;
}

void TWorld::Start() {
    startTimer(20);
}

void TWorld::PlayerEnter(quint32 id) {
    qDebug() << Q_FUNC_INFO;
    TPlayer* player = new TPlayer(id, this);
    connect(player, SIGNAL(SpawnBullet(TBullet*)), SLOT(SpawnBullet(TBullet*)));
    Players.insert(id, player);
}

void TWorld::PlayerExit(quint32 id) {
    auto playerIt = Players.find(id);
    if (playerIt != Players.end())
    {
        playerIt.value()->deleteLater();
        Players.erase(playerIt);
    }
}

void TWorld::timerEvent(QTimerEvent *) {
    //TODO: Make physics
    for (auto i = Players.begin(); i != Players.end(); i++)
    {
        i.value()->ApplyCustomPhysics();
    }

    auto i = Bullets.begin();
    while (i != Bullets.end())
    {
        (*i)->ApplyCustomPhysics();
        if ((*i)->GetTtl()<=0) {
            (*i)->deleteLater();
            i = Bullets.erase(i++);
        } else {
            i++;
        }
    }

    float step = 1.0f / 50.0f;
    qint32 velocityIterations = 6;
    qint32 positionIterations = 2;
    B2World->Step(step, velocityIterations, positionIterations);
}

void TWorld::SpawnBullet(TBullet* bullet) {
    Bullets.insert(Bullets.end(), bullet);
}
