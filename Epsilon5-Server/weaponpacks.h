#pragma once

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

struct TTimeKey {
    size_t PlayerId;
    Epsilon5::Weapon WeaponType;
    operator QString() {
        return ToString(PlayerId) + ":" + ToString((size_t)(WeaponType));
    }
};

struct TShootInfo {
    TShootInfo() {
        MachineGunAmmoInClip = 30;
        MachineGunClips = 4;

        ShotGunAmmoInClip = 8;
        ShotGunClips = 3;

        PistolAmmoInClip = 12; //usp 45
        PistolClips = 5;
        Time.start();
    }

    QTime Time;
    int MachineGunAmmoInClip;
    int MachineGunClips;
    int ShotGunAmmoInClip;
    int ShotGunClips;
    int PistolAmmoInClip;
    int PistolClips;
};

class TWeaponPacks : public QObject
{
    Q_OBJECT
public:
    TWeaponPacks(QObject *parent = 0);
public slots:
    void ActivateWeapon(TFireInfo& fireInfo);
signals:
    void SpawnBullet(TBullet *bullet);
private:
    QHash<QString, TShootInfo> LastShoots;
    static const int shotgunReloadTime = 3500;
    static const int machinegunReloadTime = 2000;
    static const int pistolReloadTime = 800;
};
