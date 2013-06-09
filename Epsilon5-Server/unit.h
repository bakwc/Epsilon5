#pragma once

#include <QTime>
#include "object.h"
#include "defines.h"

struct TWeaponInfo {
    Epsilon5::Weapon WeaponType;
    size_t BulletsLeft;
    size_t CagesLeft;
    QTime LastShoot;
};

class TUnit : public TObject
{
    Q_OBJECT
public:
    explicit TUnit(ETeam team, const TObjectParams& params, QObject* parent = 0);
    inline size_t GetHP() { return HP; }
    inline ETeam GetTeam() {
      return Team;
    }
    inline bool GetTeamBool() {
      return Team == T_One;
    }
    inline TWeaponInfo GetWeaponInfo() {
        return WeaponPack[SelectedWeapon];
    }
    inline qreal GetAimAngle() {
        return AimAngle;
    }
    virtual size_t GetPlayerId() {
        return (size_t)-1;
    }
    inline void ResetLastShoot() {
        WeaponPack[SelectedWeapon].LastShoot.restart();
    }
    inline qreal GetBulletSpawnDistance() {
        qDebug() << GetRadius();
        return GetRadius() + 0.1;
    }
protected:
    ETeam Team = T_Neutral;
    size_t HP;
    size_t SelectedWeapon = 0;
    qreal AimAngle = 0;
    QHash<size_t, TWeaponInfo> WeaponPack;
};
