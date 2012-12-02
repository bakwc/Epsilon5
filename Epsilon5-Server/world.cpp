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
const size_t WORLD_FULL_PACKET_RESEND_COUNT = 80; // Resend full packet after 50 regular packets

TWorld::TWorld(QObject *parent)
    : QObject(parent)
    , B2World(new b2World(b2Vec2(0, 0)))
    , FullPacketResendTtl(0)
{
    B2World->ClearForces();
    B2World->SetContactListener(this);
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
    bool needFullPacket = false;

    if (FullPacketResendTtl == 0) {
        needFullPacket = true;
        FullPacketResendTtl = WORLD_FULL_PACKET_RESEND_COUNT;
    } else {
        FullPacketResendTtl--;
    }

    Epsilon5::World world;
    world.clear_bullets();
    world.clear_players();

    for (auto i = Players.begin(); i != Players.end(); i++)
    {
        auto player = world.add_players();
        player->set_id(i.key());
        player->set_x(i.value()->GetX() * OBJECT_SCALE_UP);
        player->set_y(i.value()->GetY() * OBJECT_SCALE_UP);

        if (needFullPacket) {
            player->set_vx(i.value()->GetVx() * OBJECT_SCALE_UP);
            player->set_vy(i.value()->GetVy() * OBJECT_SCALE_UP);
            player->set_angle(i.value()->GetAngle());
            QByteArray playerName = i.value()->GetNickname().toLocal8Bit();
            player->set_name(playerName.data(), playerName.size());
        }
        player->set_hp(i.value()->GetHP());
    }

    for (auto i = Bullets.begin(); i != Bullets.end();i++)
    {
        auto bullet=world.add_bullets();
        bullet->set_x((*i)->GetX() * OBJECT_SCALE_UP);
        bullet->set_y((*i)->GetY() * OBJECT_SCALE_UP);
        if (needFullPacket) {
            bullet->set_vx((*i)->GetVx() * OBJECT_SCALE_UP);
            bullet->set_vy((*i)->GetVy() * OBJECT_SCALE_UP);
        }
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

    //Application()->GetMaps()->

    QByteArray result;
    result.resize(world.ByteSize());
    world.SerializeToArray(result.data(), result.size());
    return result;
}

void TWorld::Start() {
    startTimer(20);
}

void TWorld::PlayerSpawn(size_t id) {
    TPlayer* player = new TPlayer(id, Application()->GetMaps(), this);
    connect(player, SIGNAL(SpawnBullet(TBullet*)), SLOT(SpawnBullet(TBullet*)));
    connect(player, SIGNAL(Death(size_t)), SLOT(PlayerKill(size_t)));
    Players.insert(id, player);
}

void TWorld::PlayerKill(size_t id) {
    auto playerIt = Players.find(id);
    if (playerIt != Players.end()) {
        playerIt.value()->deleteLater();
        Players.erase(playerIt);
    }
}

void TWorld::timerEvent(QTimerEvent *) {
    for (auto i = Players.begin(); i != Players.end(); i++) {
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
    qDebug() << Q_FUNC_INFO;
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
void TWorld::spawnStaticObject(TStaticObjectsList &container, size_t id,
                       double x, double y, const QSizeF &size, double angle)
{
    TStaticObject* object = new TStaticObject(OBJECT_SCALE_DOWN * x,
                                     OBJECT_SCALE_DOWN * y, angle, this);
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
    TDynamicObject* object = new TDynamicObject(OBJECT_SCALE_DOWN * x,
                                           OBJECT_SCALE_DOWN * y, vx,
                                           vy, angle, this);
    object->SetRectSize(OBJECT_SCALE_DOWN * size.width(),
                        OBJECT_SCALE_DOWN * size.height());
    object->SetId(id);
    container.insert(container.end(), object);
}

//   Collisions processing
// All bodies should have user data of type TObjectInfo with object information (type, pointer to object)
void TWorld::BeginContact(b2Contact* contact) {
    void* obj1Data = contact->GetFixtureA()->GetBody()->GetUserData();
    void* obj2Data = contact->GetFixtureB()->GetBody()->GetUserData();

    TPlayer* player = 0;
    TBullet* bullet = 0;
    if (obj1Data && obj2Data) {
        TObjectInfo* obj1Info = (TObjectInfo*)obj1Data;
        TObjectInfo* obj2Info = (TObjectInfo*)obj2Data;

        if (obj1Info->ObjType == TObjectInfo::OT_Player &&
                obj2Info->ObjType == TObjectInfo::OT_Bullet)
        {
            player = (TPlayer*)(obj1Info->Object);
            bullet = (TBullet*)(obj2Info->Object);
        } else if (obj1Info->ObjType == TObjectInfo::OT_Bullet &&
                obj2Info->ObjType == TObjectInfo::OT_Player)
        {
            player = (TPlayer*)(obj2Info->Object);
            bullet = (TBullet*)(obj1Info->Object);
        }
    }

    if (player) {
        player->Hit();
    }
    if (bullet) {
        bullet->Destroy();
    }
}
