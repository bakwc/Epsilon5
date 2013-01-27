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

QPointF TWeaponBase::GetSpeed(size_t speed, double angle) {
    QPointF res;
    res.setX(speed * sin(angle + M_PI / 2));
    res.setY(speed * cos(angle + M_PI / 2));
    return res;
}

QPointF TWeaponBase::GetPosition(const QPointF& speed, const QPointF& pos) {
    QPointF res;
    res.setX(pos.x() + 1.6*speed.x()/qAbs(speed.x()));
    res.setY(pos.y() + 1.6*speed.y()/qAbs(speed.y()));
    return res;
}

QPointF TWeaponBase::GetRanomizedSpeed(const QPointF& speed) {
    return QPointF(speed.x() + rand()%10, speed.y() + rand()%10);
}

void TWeaponBase::EmitShoot(const QPointF& position, const QPointF& speed,
                            const TFireInfo& fireInfo, Epsilon5::Bullet_Type bulletType) {
    TBullet* bullet = new TBullet(position, speed, bulletType,
                                  fireInfo.PlayerId, fireInfo.Team,
                                  ((TApplication*)(qApp))->GetWorld());
    emit SpawnBullet(bullet);
}

TPistolWeapon::TPistolWeapon(QObject *parent)
    : TWeaponBase(800, 12, 5, 400, Epsilon5::Pistol, parent)
{
}

void TPistolWeapon::MakeShot(const TFireInfo& fireInfo) {
    QPointF speed = GetSpeed(200, fireInfo.Angle);
    QPointF position = GetPosition(speed, fireInfo.Pos);
    EmitShoot(position, speed, fireInfo, Epsilon5::Bullet_Type_ARBUZ);
}

TMachineGunWeapon::TMachineGunWeapon(QObject* parent)
    : TWeaponBase(2000, 30, 4, 220, Epsilon5::Machinegun, parent)
{
}

void TMachineGunWeapon::MakeShot(const TFireInfo& fireInfo) {
    QPointF speed = GetSpeed(200, fireInfo.Angle);
    QPointF position = GetPosition(speed, fireInfo.Pos);
    EmitShoot(position, speed, fireInfo, Epsilon5::Bullet_Type_LITTLE_BULLET);
}

TShotGunWeapon::TShotGunWeapon(QObject* parent)
    : TWeaponBase(3500, 8, 4, 900, Epsilon5::Shotgun, parent)
{
}

void TShotGunWeapon::MakeShot(const TFireInfo& fireInfo) {
    QPointF speed = GetSpeed(200, fireInfo.Angle);
    QPointF position = GetPosition(speed, fireInfo.Pos);
    for (size_t i = 0; i < 5; i++) {
        EmitShoot(position, GetRanomizedSpeed(speed), fireInfo, Epsilon5::Bullet_Type_LITTLE_BULLET);
    }
}


TWeaponPacks::TWeaponPacks(QObject *parent)
    : QObject(parent)
{
    Weapons.insert(Epsilon5::Pistol, new TPistolWeapon(this));
    Weapons.insert(Epsilon5::Machinegun, new TMachineGunWeapon(this));
    Weapons.insert(Epsilon5::Shotgun, new TShotGunWeapon(this));
}

QHash<size_t, TWeaponInfo> TWeaponPacks::GetPack(size_t packId) {
    Q_UNUSED(packId); // TODO: we need several different packs here
    QHash<size_t, TWeaponInfo> pack;
    pack.insert(0, Weapons[Epsilon5::Pistol]->GetDefault());
    pack.insert(1, Weapons[Epsilon5::Machinegun]->GetDefault());
    pack.insert(2, Weapons[Epsilon5::Shotgun]->GetDefault());
    return pack;
}

void TWeaponPacks::ActivateWeapon(TFireInfo& fireInfo) {
    Epsilon5::Weapon weaponType = fireInfo.WeaponInfo->WeaponType;
    size_t& bulletsLeft = fireInfo.WeaponInfo->BulletsLeft;
    size_t& cagesLeft = fireInfo.WeaponInfo->CagesLeft;
    QTime& shotTime = fireInfo.WeaponInfo->LastShoot;

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

    if (shotTime.elapsed() <= (int)Weapons[weaponType]->GetTimeBetweenShots()) {
        // Still waiting
        return;
    }

    Weapons[weaponType]->MakeShot(fireInfo);
    bulletsLeft--;
    shotTime.restart();
}


