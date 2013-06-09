#include <qmath.h>
#include <QDebug>
#include <QPointer>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "weaponpacks.h"
#include "application.h"

TWeaponBase::TWeaponBase(size_t rechargeTime,
                         size_t bulletsCount,
                         size_t cagesCount,
                         size_t timeBetweenShots,
                         Epsilon5::Weapon weaponType,
                         QObject* parent)
    : QObject(parent)
    , RechargeTime(rechargeTime)
    , BulletsCount(bulletsCount)
    , CagesCount(cagesCount)
    , TimeBetweenShots(timeBetweenShots)
    , WeaponType(weaponType)
{
    TWeaponPacks* p = (TWeaponPacks*)parent;
    connect(this, SIGNAL(SpawnBullet(TBullet*)), p, SIGNAL(SpawnBullet(TBullet*)));
}

QPointF TWeaponBase::GetSpeed(size_t speed, qreal angle) {
    QPointF res;
    res.setX(speed * sin(angle + M_PI / 2));
    res.setY(speed * cos(angle + M_PI / 2));
    return res;
}

QPointF TWeaponBase::GetPosition(const QPointF& speed, const QPointF& pos, qreal distance) {
    QPointF res;
    res.setX(pos.x() + distance * speed.x() / qAbs(speed.x()));
    res.setY(pos.y() + distance * speed.y() / qAbs(speed.y()));
    return res;
}

QPointF TWeaponBase::GetRanomizedSpeed(const QPointF& speed) {
    return QPointF(speed.x() + rand()%10, speed.y() + rand()%10);
}

void TWeaponBase::EmitShoot(const QPointF& position, const QPointF& speed,
                            TUnit* player, Epsilon5::Bullet_Type bulletType)
{
    TBullet* bullet = CreateBullet(position, speed, bulletType,
                                   player->GetPlayerId(), player->GetTeam(),
                                   ((TApplication*)(qApp))->GetWorld());
    emit SpawnBullet(bullet);
}

TPistolWeapon::TPistolWeapon(QObject *parent)
    : TWeaponBase(800, 12, 5, 400, Epsilon5::Pistol, parent)
{
}

void TPistolWeapon::MakeShot(TUnit* player) {
    QPointF speed = GetSpeed(200, player->GetAimAngle());
    QPointF position = GetPosition(speed, player->GetPosition(), player->GetBulletSpawnDistance());
    EmitShoot(position, speed, player, Epsilon5::Bullet_Type_ARBUZ);
}

TMachineGunWeapon::TMachineGunWeapon(QObject* parent)
    : TWeaponBase(2000, 30, 4, 220, Epsilon5::Machinegun, parent)
{
}

void TMachineGunWeapon::MakeShot(TUnit *player) {
    QPointF speed = GetSpeed(200, player->GetAimAngle());
    QPointF position = GetPosition(speed, player->GetPosition(), player->GetBulletSpawnDistance());
    EmitShoot(position, speed, player, Epsilon5::Bullet_Type_LITTLE_BULLET);
}

TShotGunWeapon::TShotGunWeapon(QObject* parent)
    : TWeaponBase(3500, 8, 4, 900, Epsilon5::Shotgun, parent)
{
}

void TShotGunWeapon::MakeShot(TUnit *player) {
    QPointF speed = GetSpeed(200, player->GetAimAngle());
    QPointF position = GetPosition(speed, player->GetPosition(), player->GetBulletSpawnDistance());
    for (size_t i = 0; i < 5; i++) {
        EmitShoot(position, GetRanomizedSpeed(speed), player, Epsilon5::Bullet_Type_LITTLE_BULLET);
    }
}


TWeaponPacks::TWeaponPacks(QObject *parent)
    : QObject(parent)
{
    Weapons.insert(Epsilon5::Pistol, new TPistolWeapon(this));
    Weapons.insert(Epsilon5::Machinegun, new TMachineGunWeapon(this));
    Weapons.insert(Epsilon5::Shotgun, new TShotGunWeapon(this));
    Weapons.insert(Epsilon5::Grenade, new TGrenadeWeapon(this));
    Weapons.insert(Epsilon5::Rocket, new TRocketWeapon(this));
}

QHash<size_t, TWeaponInfo> TWeaponPacks::GetPack(size_t packId) {
    QHash<size_t, TWeaponInfo> pack;
    switch (packId) {
    case 0:
        pack.insert(0, Weapons[Epsilon5::Pistol]->GetDefault());
        pack.insert(1, Weapons[Epsilon5::Machinegun]->GetDefault());
        pack.insert(2, Weapons[Epsilon5::Shotgun]->GetDefault());
        pack.insert(3, Weapons[Epsilon5::Grenade]->GetDefault());
        pack.insert(4, Weapons[Epsilon5::Rocket]->GetDefault());
        break;
    default:
        pack.insert(0, Weapons[Epsilon5::Rocket]->GetDefault());
        pack.insert(1, Weapons[Epsilon5::Machinegun]->GetDefault());
        break;
    }
    return pack;
}

void TWeaponPacks::ActivateWeapon(TUnit *player) {
    auto weaponType = player->GetWeaponInfo().WeaponType;
    auto bulletsLeft = player->GetWeaponInfo().BulletsLeft;
    auto cagesLeft = player->GetWeaponInfo().CagesLeft;
    auto shotTime = player->GetWeaponInfo().LastShoot;

    if (bulletsLeft == 0) {
        if (cagesLeft == 0) {
            // No amo - no shots
            return;
        }
        if (shotTime.elapsed() > (int)Weapons[weaponType]->GetRechargeTime()) {
            cagesLeft--;
            bulletsLeft = Weapons[weaponType]->GetBulletsCount();
        } else {
            // Not recharged yet
            return;
        }
    }

    Q_ASSERT(bulletsLeft > 0 && "something wrong with bullets number");

    qDebug() << shotTime.elapsed() << (int)Weapons[weaponType]->GetTimeBetweenShots();

    if (shotTime.elapsed() <= (int)Weapons[weaponType]->GetTimeBetweenShots()) {
        // Still waiting
        return;
    }

    Weapons[weaponType]->MakeShot(player);
    bulletsLeft--;
    player->ResetLastShoot();
}


void TGrenadeWeapon::MakeShot(TUnit *player) {
    QPointF speed = GetSpeed(200, player->GetAimAngle());
    QPointF position = GetPosition(speed, player->GetPosition(), player->GetBulletSpawnDistance());
    EmitShoot(position, speed, player, Epsilon5::Bullet_Type_GRENADE);
}


TGrenadeWeapon::TGrenadeWeapon(QObject *parent)
    : TWeaponBase(800, 12, 5, 400, Epsilon5::Grenade, parent)
{
}


TRocketWeapon::TRocketWeapon(QObject *parent)
    : TWeaponBase(1200, 8, 3, 600, Epsilon5::Grenade, parent)
{
}

void TRocketWeapon::MakeShot(TUnit *player) {
    QPointF speed = GetSpeed(200, player->GetAimAngle());
    QPointF position = GetPosition(speed, player->GetPosition(), player->GetBulletSpawnDistance());
    EmitShoot(position, speed, player, Epsilon5::Bullet_Type_ROCKET);
}
