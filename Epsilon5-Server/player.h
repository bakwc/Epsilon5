#pragma once

#include <QTime>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "object.h"
#include "unit.h"
#include "maps.h"

#include "../utils/uexception.h"

class TBullet;
class TApplication;
class TVehicleBase;

class TPlayer : public TUnit
{
    Q_OBJECT
public:
    TPlayer(size_t id, ETeam team, QObject *parent = 0);
    inline size_t GetId() { return Id; }
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
    void OnEnteredVehicle(TVehicleBase* vehicle);
    void OnLeftVehicle();
    inline TVehicleBase* GetVehicle() {
        if (Vehicle == nullptr) {
            throw UException("Player is not in vehicle");
        }
        return Vehicle;
    }
    inline bool InVehicle() {
        return Vehicle != nullptr;
    }
    virtual size_t GetPlayerId() {
        return Id;
    }
signals:
    void Fire(TUnit* player);
    void Death(size_t id);
    void Killed(size_t playerId);
    void EnteredVehicle(size_t id);
    void LeftVehicle(size_t id);
public slots:
    void ApplyControl(const Epsilon5::Control& control);
    void Hit(size_t playerId, quint8 ffMode = 100);
    void ApplyDamage(qreal dmg, size_t playerId);
private:
    TApplication* Application();
private:
    b2Vec2 Force;
    size_t Id;
    QString NickName;
    int Ping;
    QTime LastVehicleEnter;
    TVehicleBase* Vehicle = nullptr;
};
