#pragma once

#include <QObject>
#include <QHash>
#include <QTime>
#include <QString>
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
