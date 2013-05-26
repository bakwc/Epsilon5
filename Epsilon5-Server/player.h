#pragma once

#include <QTime>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "dynamicobject.h"
#include "maps.h"

#include "../utils/uexception.h"

class TBullet;
class TApplication;
class TVehicleBase;

struct TWeaponInfo {
    Epsilon5::Weapon WeaponType;
    size_t BulletsLeft;
    size_t CagesLeft;
    QTime LastShoot;
};

struct TFireInfo {
    QPointF Pos, Speed;
    double Angle;
    size_t PlayerId;
    ETeam Team;
    TWeaponInfo* WeaponInfo = 0;
};

class TPlayer : public TDynamicObject
{
    Q_OBJECT
public:
    TPlayer(size_t id, ETeam team, TMaps* maps, QObject *parent = 0);
    inline size_t GetId() { return Id; }
    inline size_t GetHP() { return HP; }
    void Hit(size_t playerId, quint8 ffMode = 100);
    void ApplyCustomPhysics();
    void SetNickname(const QString& nickName);
    inline QString GetNickname() {
        return NickName;
    }
    inline void SetPing(int ping) {
        Ping = ping;
    }
    inline int GetPing() {
        return Ping;
    }
    inline ETeam GetTeam() {
        return Team;
    }
    inline bool GetTeamBool() {
        return Team == T_One;
    }
    void OnEnteredVehicle(TVehicleBase* vehicle);
    void OnLeftVehicle();
    inline TVehicleBase* GetVehicle() {
        if (Vehicle == nullptr) {
            throw UException("Player is not in vehicle");
        }
        return Vehicle;
    }
signals:
    void Death(size_t id);
    void Killed(size_t playerId);
    void Fire(TFireInfo& fireInfo);
    void EnteredVehicle(size_t id);
    void LeftVehicle(size_t id);
public slots:
    void ApplyControl(const Epsilon5::Control& control);
private:
    TApplication* Application();
private:
    b2Vec2 Force;
    size_t Id;
    QString NickName;
    TMaps* Maps;
    size_t HP = 100;
    TObjectInfo CollisionInfo;
    ETeam Team;
    int Ping;
    QHash<size_t, TWeaponInfo> WeaponPack;
    size_t SelectedWeapon = 0;
    QTime LastVehicleEnter;
    TVehicleBase* Vehicle = nullptr;
};
