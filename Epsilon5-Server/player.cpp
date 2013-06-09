#include <qmath.h>
#include <QDebug>
#include <QRect>
#include "player.h"
#include "bullet.h"
#include "defines.h"
#include "application.h"

const size_t HP_LOST = 45;

TPlayer::TPlayer(size_t id, ETeam team, QObject *parent)
    : TUnit(team, TObjectParams(1.5), parent)
    , Id(id)
{
    Body->SetUserData(this);
    ObjectType = OT_Player;

    HP = 100;

    Force(0) = 0;
    Force(1) = 0;

    WeaponPack = Application()->GetWeaponPacks()->GetPack(0); // TODO: pack number should be passed

    LastVehicleEnter.start();
}

void TPlayer::ApplyControl(const Epsilon5::Control &control) {
    if (control.keystatus().keyenter() &&
            LastVehicleEnter.elapsed() > 1000)
    {
        if (Vehicle == nullptr) {
            emit EnteredVehicle(Id);
        } else {
            emit LeftVehicle(Id);
        }
    }

    if (Vehicle != nullptr) {
        Vehicle->ApplyControl(control);
        return;
    }
    try {
        if (control.keystatus().keydown()) Force(1) = 10;
        else if (control.keystatus().keyup()) Force(1) = -10;
        else Force(1) = 0;

        if (control.keystatus().keyleft()) Force(0) = -10;
        else if (control.keystatus().keyright()) Force(0) = 10;
        else Force(0)=0;

        AimAngle = control.angle();

        size_t weaponId = control.weapon();

        if (WeaponPack.find(weaponId) != WeaponPack.end()) {
            SelectedWeapon = weaponId;
        }

        if (control.keystatus().keyattack1() ||
                control.keystatus().keyattack2())
        {
            emit Fire(this);
        }
    } catch (const std::exception& e) {
        qDebug() << "TPlayer::ApplyControl(): " << e.what();
    }
}

void TPlayer::ApplyCustomPhysics()
{
    // If player is in vehicle, just take players coordinated from vehicle
    if (Vehicle != nullptr) {
        SetPosition(Vehicle->GetPosition());
        return;
    }
    const TMaps* const maps = GApp->GetMaps();

    qDebug() << GetPosition();

    const double coeff = maps->GetFrictionByPos(GetPosition());

    Force *= coeff;

    // Really apply physics
    Body->ApplyLinearImpulse(Force, Body->GetPosition());
}

void TPlayer::SetNickname(const QString& nickName) {
    NickName = nickName;
}

void TPlayer::OnEnteredVehicle(TVehicleBase* vehicle) {
    LastVehicleEnter.restart();
    Vehicle = vehicle;
    DeActivate();
}

void TPlayer::OnLeftVehicle() {
    LastVehicleEnter.restart();
    Vehicle = nullptr;
    Activate();
    // todo: select correct player position
}

void TPlayer::ApplyDamage(qreal dmg, size_t playerId) {
    int resultHp = HP - dmg;
    if (resultHp <= 0) {
        if (GWorld->GetPlayer(playerId)->GetTeam() !=
                GetTeam())
        {
            emit Killed(playerId);
        }
        emit Death(Id);
        return;
    }
    HP = resultHp;
}

void TPlayer::Hit(size_t playerId, quint8 ffMode) {
    size_t hpDelta = HP_LOST * (ffMode > 100 ? 1 : ffMode*0.01);
    if (HP <= hpDelta) {
        emit Killed(playerId);
        emit Death(Id);
        return;
    }
    HP -= hpDelta;
}

TApplication* TPlayer::Application() {
    return (TApplication*)qApp;
}
