#include "player.h"
#include "bullet.h"
#include <QDebug>

const float PI=3.1415926f;

TPlayer::TPlayer(size_t id, QObject *parent)
    : TDynamicObject(0, 0, 0, 0, 0, parent)
    , Id(id)
{
    b2CircleShape circle;
    circle.m_p.Set(0, 0);
    circle.m_radius = 1.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 0.8f;
    fixtureDef.filter.groupIndex = 1;
    Body->CreateFixture(&fixtureDef);

    lastShoot.start();
}

void TPlayer::ApplyControl(const Epsilon5::Control &control) {
    if (control.keystatus().keydown()) Force(1) = 50;
    else if (control.keystatus().keyup()) Force(1) = -50;
    else Force(1) = 0;

    if (control.keystatus().keyleft()) Force(0) = -50;
    else if (control.keystatus().keyright()) Force(0) = 50;
    else Force(0)=0;

    double angle = control.angle();

    if ((control.keystatus().keyattack1()
            || control.keystatus().keyattack2())
            && lastShoot.elapsed() > 500)   // FIRE!!
    {
        lastShoot.restart();
        TBullet *bullet;
        if (control.keystatus().keyattack1()) {
            double x, y, vx, vy;
            vx = 28 * sin(angle + PI / 2);
            vy = 28 * cos(angle + PI / 2);
            x = GetX() + vx / 10;
            y = GetY() + vy / 10;
            bullet = new TBullet(x, y, vx, vy, 12.5, parent());
        } else {
            qDebug() << "Control 2!";
            bullet = new TBullet(GetX() + 2, GetY(), 0, 0, 0.8, parent());
        }
        emit SpawnBullet(bullet);
    }

    //setAngle(control.angle());
}

void TPlayer::ApplyCustomPhysics()
{
    b2Vec2 FractionForce = (-5) * Body->GetLinearVelocity();
    b2Vec2 totalForce = Force + FractionForce;
    Body->ApplyForceToCenter(totalForce);
}

void TPlayer::SetNickname(const QString& nickName) {
    NickName = nickName;
}
