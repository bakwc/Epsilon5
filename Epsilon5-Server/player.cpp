#include <qmath.h>
#include <QDebug>
#include <QRect>
#include "player.h"
#include "bullet.h"
#include "defines.h"
#include "application.h"

const size_t HP_LOST = 45;

TPlayer::TPlayer(size_t id, ETeam team, TMaps *maps, QObject *parent)
    : TDynamicObject(TObjectParams(1.5), parent)
    , Id(id)
    , Maps(maps)
    , Team(team)
{
    Body->SetUserData(&CollisionInfo);

    CollisionInfo.ObjType = TObjectInfo::OT_Player;
    CollisionInfo.Object = this;

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

        double angle = control.angle();

        if (control.keystatus().keyattack1() ||
                control.keystatus().keyattack2())
        {
            TFireInfo fireInfo;
            fireInfo.Pos = GetPosition();
            fireInfo.Speed = GetSpeed();
            fireInfo.Angle = angle;

            size_t weaponId = control.weapon();

            if (WeaponPack.find(weaponId) != WeaponPack.end()) {
                SelectedWeapon = weaponId;
            }

            fireInfo.PlayerId = Id;
            // Secondary attack depricated
            //fireInfo.PrimaryAttack = control.keystatus().keyattack1();
            fireInfo.Team = GetTeam();
            fireInfo.WeaponInfo = &WeaponPack[SelectedWeapon];
            emit Fire(fireInfo);
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

    // Really apply physics
    Body->ApplyLinearImpulse(Force, Body->GetPosition());

    QSize mapSize = Maps->GetMapSize();

    b2Vec2 pos = Body->GetPosition();
    b2Vec2 speed = Body->GetLinearVelocity();
    const quint8 PLAYGROUND_BORDER_SIZE = 100;
    QRectF playgroundBorders = QRectF(
            -mapSize.width() / 2 + PLAYGROUND_BORDER_SIZE,
            -mapSize.height() / 2 + PLAYGROUND_BORDER_SIZE,
            mapSize.width() - 2 * PLAYGROUND_BORDER_SIZE,
            mapSize.height() - 2 * PLAYGROUND_BORDER_SIZE);

    if (pos(0) * 10 > playgroundBorders.right()) {
        speed(0) = 0;
        pos(0) = 0.1 * (playgroundBorders.right() - 1);
        Body->SetTransform(pos, Body->GetAngle());
        Body->SetLinearVelocity(speed);
    }

    if (pos(1) * 10 > playgroundBorders.bottom()) {
        speed(1) = 0;
        pos(1) = 0.1 * (playgroundBorders.bottom() - 1);
        Body->SetTransform(pos, Body->GetAngle());
        Body->SetLinearVelocity(speed);
    }

    if (pos(0) * 10 < playgroundBorders.left()) {
        speed(0) = 0;
        pos(0) = 0.1 * (playgroundBorders.left() + 1);
        Body->SetTransform(pos, Body->GetAngle());
        Body->SetLinearVelocity(speed);
    }

    if (pos(1) * 10 < playgroundBorders.top()) {
        speed(1) = 0;
        pos(1) = 0.1 * (playgroundBorders.top() + 1);
        Body->SetTransform(pos, Body->GetAngle());
        Body->SetLinearVelocity(speed);
    }
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

void TPlayer::ApplyDamage(float dmg, size_t playerId) {
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
