#pragma once

#include <memory>
#include <QObject>
#include <QHash>
#include <QTime>
#include <QString>
#include <QTimer>
#include "../utils/ucast.h"
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "player.h"

class TWorld;
class TBullet;

class TWeaponBase : public QObject {
    Q_OBJECT
public:
    TWeaponBase(size_t rechargeTime, size_t bulletsCount,
                size_t cagesCount, size_t timeBetweenShots,
                Epsilon5::Weapon weaponType, QObject* parent);
    inline size_t GetRechargeTime() {
        return RechargeTime;
    }
    inline size_t GetBulletsCount() {
        return BulletsCount;
    }
    inline size_t GetCagesCount() {
        return CagesCount;
    }
    inline size_t GetTimeBetweenShots() {
        return TimeBetweenShots;
    }
    inline TWeaponInfo GetDefault() {
        TWeaponInfo info;
        info.BulletsLeft = BulletsCount;
        info.CagesLeft = CagesCount;
        info.WeaponType = WeaponType;
        info.LastShoot.start();
        return info;
    }

    virtual void MakeShot(const TFireInfo& fireInfo) = 0;
signals:
    void SpawnBullet(TBullet* bullet);
private:
    size_t RechargeTime;
    size_t BulletsCount;
    size_t CagesCount;
    size_t TimeBetweenShots;
    Epsilon5::Weapon WeaponType;
};

class TPistolWeapon : public TWeaponBase {
    Q_OBJECT
public:
    TPistolWeapon(QObject* parent);
    void MakeShot(const TFireInfo& fireInfo);
};

class TMachineGunWeapon : public TWeaponBase {
    Q_OBJECT
public:
    TMachineGunWeapon(QObject* parent);
    void MakeShot(const TFireInfo& fireInfo);
};

class TShotGunWeapon : public TWeaponBase {
    Q_OBJECT
public:
    TShotGunWeapon(QObject* parent);
    void MakeShot(const TFireInfo& fireInfo);
};

class TWeaponPacks : public QObject
{
    Q_OBJECT
public:
    TWeaponPacks(QObject *parent = 0);
    QHash<size_t, TWeaponInfo> GetPack(size_t packId);
public slots:
    void ActivateWeapon(TFireInfo& fireInfo);
signals:
    void SpawnBullet(TBullet* bullet);
private:
    QHash<Epsilon5::Weapon, TWeaponBase*> Weapons;
};
