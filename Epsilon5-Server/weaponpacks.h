#pragma once

#include <QObject>
#include <QHash>
#include <QTime>
#include <QString>
#include "../utils/ucast.h"
#include "player.h"

class TWorld;
class TBullet;

enum EWeaponType {
    WT_Pistol,
    WT_Machinegun,
    WT_Shotgun
};

struct TTimeKey {
    size_t PlayerId;
    EWeaponType WeaponType;
    operator QString() {
        return ToString(PlayerId) + ":" + ToString((size_t)(WeaponType));
    }
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
    QHash<QString, QTime> LastShoots;
};
