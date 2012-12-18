#include <QRect>
#include <QSize>
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include "../utils/uexception.h"
#include "application.h"
#include "world.h"
#include "defines.h"

TWorld::TWorld(QObject *parent)
    : QObject(parent)
    , B2World(new b2World(b2Vec2(0, 0)))
{
    B2World->ClearForces();
    B2World->SetContactListener(this);
}

TWorld::~TWorld()
{
}

TPlayer* TWorld::GetPlayer(size_t id) {
    if (Players.find(id) == Players.end()) {
        throw UException(QString("Player #%1 not found!").arg(id));
    }
    return Players[id];
}

// Returns, if distance between player and object enought for sending packet
bool SendDistance(double x1, double y1, double x2, double y2) {
    double dx, dy;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    return (dx < 960 && dy < 540); // Half of screen (190x1080)
}

// Serialising world specially for given player
QByteArray TWorld::Serialize(size_t playerId, bool needFullPacket) {
    Epsilon5::World world;

    QPointF playerPos = GetPlayerPos(playerId);

    for (auto& p: Players) {
        auto player = world.add_players();
        player->set_id(p->GetId());
        player->set_x(p->GetX() * OBJECT_SCALE_UP);
        player->set_y(p->GetY() * OBJECT_SCALE_UP);

        if (needFullPacket) {
            player->set_vx(p->GetVx() * OBJECT_SCALE_UP);
            player->set_vy(p->GetVy() * OBJECT_SCALE_UP);
            player->set_angle(p->GetAngle());
            QByteArray playerName = p->GetNickname().toLocal8Bit();
            player->set_name(playerName.data(), playerName.size());
            player->set_ping(p->GetPing());
        }
        player->set_hp(p->GetHP());
        player->set_team(p->GetTeamBool());
    }

    for (auto& b: Bullets) {
        // Filtering bullets on large distances
        if (!SendDistance(b->GetX() * OBJECT_SCALE_UP,
                b->GetY() * OBJECT_SCALE_UP,
                playerPos.x() * OBJECT_SCALE_UP,
                playerPos.y() * OBJECT_SCALE_UP))
        {
            continue;
        }

        auto bullet=world.add_bullets();
        bullet->set_x(b->GetX() * OBJECT_SCALE_UP);
        bullet->set_y(b->GetY() * OBJECT_SCALE_UP);
        bullet->set_bullet_type(b->GetType());
        if (needFullPacket) {
            bullet->set_vx(b->GetVx() * OBJECT_SCALE_UP);
            bullet->set_vy(b->GetVy() * OBJECT_SCALE_UP);
        }
        bullet->set_team(b->GetTeamBool());
    }

    for (auto& o: StaticObjects) {
        auto object = world.add_objects();
        object->set_x(o->GetX() * OBJECT_SCALE_UP);
        object->set_y(o->GetY() * OBJECT_SCALE_UP);
        object->set_angle(o->GetAngle());
        object->set_id(o->GetId());
    }

    for (auto& o: DynamicObjects) {
        // Filtering DynamicObjects on large distances
        if (!SendDistance(o->GetX() * OBJECT_SCALE_UP,
                o->GetY() * OBJECT_SCALE_UP,
                playerPos.x() * OBJECT_SCALE_UP,
                playerPos.y() * OBJECT_SCALE_UP))
        {
            continue;
        }

        auto object = world.add_objects();
        object->set_x(o->GetX() * OBJECT_SCALE_UP);
        object->set_y(o->GetY() * OBJECT_SCALE_UP);
        object->set_angle(o->GetAngle());
        object->set_id(o->GetId());
    }

    for (auto& b: WorldBorders) {
        auto object = world.add_objects();
        object->set_x(b->GetX() * OBJECT_SCALE_UP);
        object->set_y(b->GetY() * OBJECT_SCALE_UP);
        object->set_angle(b->GetAngle());
        object->set_id(b->GetId());
    }

    if (needFullPacket) {
        Application()->GetMaps()->SerialiseRespPoints(world);
        Application()->GetServer()->SerialiseStats(world);
    }


    Epsilon5::PlayerInfo* playerInfo = world.mutable_player_info();
    if (needFullPacket) {
        playerInfo->set_bullets(10);
        playerInfo->set_cage(20);       // TODO: correct bullets and cage count
        playerInfo->set_id(playerId);
        QByteArray map = Application()->GetMaps()->GetCurrentMap().toLocal8Bit();
        playerInfo->set_map(map.data(), map.size());
        // Any other additional info here
    }

    world.set_packet_number(CurrentPacketNumber++);
    Times[CurrentPacketNumber].start();
    // TODO: check for size_t overflowing

    QByteArray data;
    data.resize(world.ByteSize());
    world.SerializeToArray(data.data(), data.size());

    return data;
}

void TWorld::Start() {
    startTimer(20);
}

void TWorld::PlayerSpawn(size_t id, ETeam team) {
    TPlayer* player = new TPlayer(id, team, Application()->GetMaps(), this);
    connect(player, SIGNAL(Death(size_t)), SLOT(PlayerKill(size_t)));
    connect(player, SIGNAL(Killed(size_t)), SIGNAL(PlayerKilled(size_t)));
    connect(player, SIGNAL(Fire(TFireInfo&)),
            Application()->GetWeaponPacks(), SLOT(ActivateWeapon(TFireInfo&)));
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

    for (auto& p: Players) {
        p->ApplyCustomPhysics();
    }

    for (auto b: Bullets) {
        if (b->GetTtl() <= 0) {
            b->deleteLater();
        }
    }

    Bullets.erase(remove_if(Bullets.begin(), Bullets.end(),
                    [](TBullet* b) {
        return b->GetTtl() <= 0;
    }), Bullets.end());

    float step = 1.0f / 50.0f;
    qint32 velocityIterations = 5;
    qint32 positionIterations = 2;
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
    for (auto i: StaticObjects) {
        i->deleteLater();
    }
    StaticObjects.clear();

    for (auto i: DynamicObjects) {
        i->deleteLater();
    }
    DynamicObjects.clear();
}

void TWorld::ClearBorders() {
    for (auto i: WorldBorders) {
        i->deleteLater();
    }
    WorldBorders.clear();
}

void TWorld::NeedFullPacket() {
    Application()->GetServer()->NeedFullPacket();
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

// Collisions processing
// All bodies should have user data of type TObjectInfo
// with object information (type, pointer to object)
void TWorld::BeginContact(b2Contact* contact) {
    void* obj1Data = contact->GetFixtureA()->GetBody()->GetUserData();
    void* obj2Data = contact->GetFixtureB()->GetBody()->GetUserData();

    TPlayer* player1 = 0;
    TPlayer* player2 = 0;

    TBullet* bullet1 = 0;
    TBullet* bullet2 = 0;

    if (obj1Data) {
        TObjectInfo* objInfo = (TObjectInfo*)obj1Data;
        if (objInfo->ObjType == TObjectInfo::OT_Player) {
            player1 = (TPlayer*)(objInfo->Object);
        }
        if (objInfo->ObjType == TObjectInfo::OT_Bullet) {
            bullet1 = (TBullet*)(objInfo->Object);
        }
    }

    if (obj2Data) {
        TObjectInfo* objInfo = (TObjectInfo*)obj2Data;
        if (objInfo->ObjType == TObjectInfo::OT_Player) {
            player2 = (TPlayer*)(objInfo->Object);
        }
        if (objInfo->ObjType == TObjectInfo::OT_Bullet) {
            bullet2 = (TBullet*)(objInfo->Object);
        }
    }

    if (player1 && bullet2 && player1->GetId() != bullet2->GetPlayerId() ) {
        player1->Hit(bullet2->GetPlayerId(),
            (player1->GetTeam() != bullet2->GetTeam())
                ? 100
                : Application()->GetSettings()->GetGameplayFriendlyFire());
    }

    if (player2 && bullet1 && player2->GetId() != bullet1->GetPlayerId()) {
        player2->Hit(bullet1->GetPlayerId(),
            (player2->GetTeam() != bullet1->GetTeam())
                ? 100
                : Application()->GetSettings()->GetGameplayFriendlyFire());
    }

    if ((bullet1 && !bullet2) || (bullet2 && !bullet1)) {
        if (bullet1) {
            bullet1->Destroy();
        } else {
            bullet2->Destroy();
        }
    }
}

QPointF TWorld::GetPlayerPos(size_t playerId) {
    if (Players.find(playerId) == Players.end()) {
        return QPointF(0, 0);
    }
    return Players[playerId]->GetPosition();
}

void TWorld::SetPingForPlayer(size_t id, size_t packetNumber) {
    if (Players.find(id) != Players.end()) {
        int ping = Times[packetNumber].elapsed();
        Players[id]->SetPing(ping);
    }
}
