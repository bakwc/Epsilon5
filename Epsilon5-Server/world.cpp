#include <QDebug>
#include <QRect>
#include <QSize>
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include "../utils/uexception.h"
#include "application.h"
#include "world.h"

const qreal OBJECT_SCALE_UP = 10;
const qreal OBJECT_SCALE_DOWN = 1 / OBJECT_SCALE_UP;
const quint16 WORLD_BORDER_SIZE = 4 * OBJECT_SCALE_UP;
const size_t WORLD_BORDER_ID = -1;

TWorld::TWorld(QObject *parent)
    : QObject(parent)
    , B2World(new b2World(b2Vec2(0, 0)))
{
    B2World->ClearForces();
}

TWorld::~TWorld()
{
    if( B2World )
    {
        delete B2World;
        B2World = NULL;
    }
}

TPlayer* TWorld::GetPlayer(size_t id) {
    if (Players.find(id) == Players.end()) {
        throw UException(QString("Player #%1 not found!").arg(id));
    }
    return Players[id];
}

QByteArray TWorld::Serialize() {
    Epsilon5::World world;
    world.clear_bullets();
    world.clear_players();

    for (auto i = Players.begin(); i != Players.end(); i++)
    {
        auto player = world.add_players();
        player->set_id(i.key());
        player->set_x(i.value()->GetX() * OBJECT_SCALE_UP);
        player->set_y(i.value()->GetY() * OBJECT_SCALE_UP);

        player->set_vx(i.value()->GetVx() * OBJECT_SCALE_UP);
        player->set_vy(i.value()->GetVy() * OBJECT_SCALE_UP);
        player->set_angle(i.value()->GetAngle());
        QByteArray playerName = i.value()->GetNickname().toLocal8Bit();
        player->set_name(playerName.data(), playerName.size());
    }

    for (auto i = Bullets.begin(); i != Bullets.end();i++)
    {
        auto bullet=world.add_bullets();
        bullet->set_x((*i)->GetX() * OBJECT_SCALE_UP);
        bullet->set_y((*i)->GetY() * OBJECT_SCALE_UP);
        bullet->set_vx((*i)->GetVx() * OBJECT_SCALE_UP);
        bullet->set_vy((*i)->GetVy() * OBJECT_SCALE_UP);
    }

    for (auto i = StaticObjects.begin(); i != StaticObjects.end(); i++) {
        auto object = world.add_objects();
        object->set_x((*i)->GetX() * OBJECT_SCALE_UP);
        object->set_y((*i)->GetY() * OBJECT_SCALE_UP);
        object->set_angle((*i)->GetAngle());
        object->set_id((*i)->GetId());
    }

    for (auto i = DynamicObjects.begin(); i != DynamicObjects.end(); i++) {
        auto object = world.add_objects();
        object->set_x((*i)->GetX() * OBJECT_SCALE_UP);
        object->set_y((*i)->GetY() * OBJECT_SCALE_UP);
        object->set_angle((*i)->GetAngle());
        object->set_id((*i)->GetId());
    }

    for (auto i = WorldBorders.begin(); i != WorldBorders.end(); i++) {
        auto object = world.add_objects();
        object->set_x((*i)->GetX() * OBJECT_SCALE_UP);
        object->set_y((*i)->GetY() * OBJECT_SCALE_UP);
        object->set_angle((*i)->GetAngle());
        object->set_id((*i)->GetId());
    }

    QByteArray result;
    result.resize(world.ByteSize());
    world.SerializeToArray(result.data(), result.size());
    return result;
}

void TWorld::Start() {
    startTimer(20);
}

void TWorld::PlayerEnter(size_t id) {
    qDebug() << Q_FUNC_INFO;
    TPlayer* player = new TPlayer(id, Application()->GetMaps(), this);
    connect(player, SIGNAL(SpawnBullet(TBullet*)), SLOT(SpawnBullet(TBullet*)));
    Players.insert(id, player);
}

void TWorld::PlayerExit(size_t id) {
    auto playerIt = Players.find(id);
    if (playerIt != Players.end())
    {
        playerIt.value()->deleteLater();
        Players.erase(playerIt);
    }
}

void TWorld::timerEvent(QTimerEvent *) {
    for (auto i = Players.begin(); i != Players.end(); i++)
    {
        i.value()->ApplyCustomPhysics();
    }

    auto i = Bullets.begin();
    while (i != Bullets.end())
    {
        (*i)->ApplyCustomPhysics();
        if ((*i)->GetTtl() > 0) {
            ++i;
            continue;
        }
        (*i)->deleteLater();
        i = Bullets.erase(i++);
    }

    float step = 1.0f / 100.0f;
    qint32 velocityIterations = 10;
    qint32 positionIterations = 8;
    B2World->Step(step, velocityIterations, positionIterations);
}

void TWorld::SpawnBullet(TBullet* bullet) {
    Bullets.insert(Bullets.end(), bullet);
}

void TWorld::SpawnObject(size_t id, int x, int y, double angle) {
    bool dynamic = Application()->GetObjects()->IsDynamicObject(id);
    QPoint size = Application()->GetObjects()->GetObjectSize(id);
    if (dynamic) {
        spawnDynamicObject(DynamicObjects, id, x, y, 0, 0,
            QSizeF(size.x(), size.y()), angle);
        return;
    }

    spawnStaticObject(StaticObjects, id, x, y, QSizeF(size.x(), size.y()), angle);
}

void TWorld::ClearObjects() {
    for (auto i = StaticObjects.begin(); i != StaticObjects.end(); i++) {
        (*i)->deleteLater();
    }
    StaticObjects.clear();

    for (auto i = DynamicObjects.begin(); i != DynamicObjects.end(); i++) {
        (*i)->deleteLater();
    }
    DynamicObjects.clear();
}

void TWorld::ClearBorders() {
    for (auto i = WorldBorders.begin(); i != WorldBorders.end(); i++) {
        (*i)->deleteLater();
    }
    WorldBorders.clear();
}

TApplication* TWorld::Application() {
    return (TApplication*)(parent());
}

void TWorld::SpawnBorders(const QSize &mapSize) {
    QSizeF objectSize;

    // Top border
    objectSize = QSizeF(mapSize.width(), WORLD_BORDER_SIZE);
    spawnStaticObject(WorldBorders, WORLD_BORDER_ID,
        0, -mapSize.height() / 2, objectSize);

    // Left border
    objectSize = QSizeF(WORLD_BORDER_SIZE, mapSize.height());
    spawnStaticObject(WorldBorders, WORLD_BORDER_ID,
        -mapSize.width() / 2, 0, objectSize);

    // Bottom border
    objectSize = QSizeF(mapSize.width(), WORLD_BORDER_SIZE);
    spawnStaticObject(WorldBorders, WORLD_BORDER_ID,
        0, mapSize.height() / 2, objectSize);

    // Right border
    objectSize = QSizeF(WORLD_BORDER_SIZE, mapSize.height());
    spawnStaticObject(WorldBorders, WORLD_BORDER_ID,
        mapSize.width() / 2, 0, objectSize);
}

// Spawn static object at (rect.x;rect.y).
// Center of the object will be in the same position.
void TWorld::spawnStaticObject(TStaticObjectsList &container,
    size_t id, double x, double y, const QSizeF &size, double angle)
{
    TStaticObject* object = new TStaticObject(
        OBJECT_SCALE_DOWN * x, OBJECT_SCALE_DOWN * y, angle, this);
    object->SetRectSize(OBJECT_SCALE_DOWN * size.width(),
        OBJECT_SCALE_DOWN * size.height());
    object->SetId(id);
    container.insert(container.end(), object);
}

// Spawn dynamic object at (rect.x;rect.y).
// Center of the object will be in the same position.
void TWorld::spawnDynamicObject(TDynamicObjectsList &container,
    size_t id, double x, double y, double vx, double vy,
    const QSizeF& size, double angle)
{
    TDynamicObject* object = new TDynamicObject(
        OBJECT_SCALE_DOWN * x, OBJECT_SCALE_DOWN * y, vx, vy, angle, this);
    object->SetRectSize(OBJECT_SCALE_DOWN * size.width(),
        OBJECT_SCALE_DOWN * size.height());
    object->SetId(id);
    container.insert(container.end(), object);
}
