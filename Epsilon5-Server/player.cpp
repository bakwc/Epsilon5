#include <qmath.h>
#include <QDebug>
#include "player.h"
#include "bullet.h"
#include "defines.h"

const size_t HP_LOST = 45;

TPlayer::TPlayer(size_t id, ETeam team, TMaps *maps, QObject *parent)
    : TDynamicObject(0, 0, 0, 0, 0, parent)
    , Id(id)
    , Maps(maps)
    , HP(100)
    , Team(team)
{
    b2Vec2 pos;
    QPoint respPos = Maps->GetSpawnPosition(team);
    pos.x = OBJECT_SCALE_DOWN * respPos.x();
    pos.y = OBJECT_SCALE_DOWN * respPos.y();
    Body->SetTransform(pos, Body->GetAngle());

    b2CircleShape circle;
    circle.m_p.Set(0, 0);
    circle.m_radius = 1.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 0.6f;
    fixtureDef.friction = 0.8f;
    fixtureDef.filter.groupIndex = 1;
    Body->CreateFixture(&fixtureDef);

    Body->SetUserData(&CollisionInfo);
    CollisionInfo.ObjType = TObjectInfo::OT_Player;
    CollisionInfo.Object = this;

    Force(0) = 0;
    Force(1) = 0;
}

void TPlayer::ApplyControl(const Epsilon5::Control &control) {
    try {
        if (control.keystatus().keydown()) Force(1) = 5.5;
        else if (control.keystatus().keyup()) Force(1) = -5.5;
        else Force(1) = 0;

        if (control.keystatus().keyleft()) Force(0) = -5.5;
        else if (control.keystatus().keyright()) Force(0) = 5.5;
        else Force(0)=0;

        double angle = control.angle();

        if (control.keystatus().keyattack1() ||
                control.keystatus().keyattack2())
        {
            TFireInfo fireInfo;
            fireInfo.X = GetX();
            fireInfo.Y = GetY();
            fireInfo.Vx = GetVx();
            fireInfo.Vy = GetVy();
            fireInfo.Angle = angle;
            fireInfo.Weapon = control.weapon();
            fireInfo.PlayerId = Id;
            fireInfo.PrimaryAttack = control.keystatus().keyattack1();
            fireInfo.Team = GetTeam();
            emit Fire(fireInfo);
        }
    } catch (const std::exception& e) {
        qDebug() << "TPlayer::ApplyControl(): " << e.what();
    }

    //setAngle(control.angle());
}

void TPlayer::ApplyCustomPhysics()
{
    //ApplyFractionForce();
    //Body->ApplyForceToCenter(Force);
    Body->ApplyLinearImpulse(Force, Body->GetPosition());

    QSize mapSize = Maps->GetMapSize();

    b2Vec2 pos = Body->GetPosition();
    b2Vec2 speed = Body->GetLinearVelocity();

    if (pos(0) * 10 > mapSize.width()/2 - 400) {
        speed(0) = 0;
        pos(0) = 0.1 * (mapSize.width()/2 - 401);
        Body->SetTransform(pos, Body->GetAngle());
        Body->SetLinearVelocity(speed);
    }

    if (pos(1) * 10 > mapSize.height()/2 - 300) {
        speed(1) = 0;
        pos(1) = 0.1 * (mapSize.height()/2 - 301);
        Body->SetTransform(pos, Body->GetAngle());
        Body->SetLinearVelocity(speed);
    }

    if (pos(0) * 10 < - mapSize.width()/2 + 400) {
        speed(0) = 0;
        pos(0) = 0.1 * (- mapSize.width()/2 + 401);
        Body->SetTransform(pos, Body->GetAngle());
        Body->SetLinearVelocity(speed);
    }

    if (pos(1) * 10 < - mapSize.height()/2 + 300) {
        speed(1) = 0;
        pos(1) = 0.1 * (- mapSize.height()/2 + 301);
        Body->SetTransform(pos, Body->GetAngle());
        Body->SetLinearVelocity(speed);
    }

}

void TPlayer::SetNickname(const QString& nickName) {
    NickName = nickName;
}

void TPlayer::Hit(size_t playerId) {
    if (HP > HP_LOST) {
        HP -= HP_LOST;
    } else {
        emit Killed(playerId);
        emit Death(Id);
    }
}
