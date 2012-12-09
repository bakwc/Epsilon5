#include <qmath.h>
#include <QDebug>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "weaponpacks.h"
#include "application.h"

TWeaponPacks::TWeaponPacks(QObject *parent)
    : QObject(parent)
{
}

void TWeaponPacks::ActivateWeapon(TFireInfo& fireInfo) {
    Epsilon5::Weapon weaponType = fireInfo.PrimaryAttack ? fireInfo.Weapon : Epsilon5::Pistol;

    TTimeKey key;
    key.PlayerId = fireInfo.PlayerId;
    key.WeaponType = weaponType;

    switch (weaponType) {
    case Epsilon5::Pistol: {
        TShootInfo& shootInfo = LastShoots[key];
        if (shootInfo.Time.elapsed() > 400) {
            shootInfo.Time.restart();
            double x, y, vx, vy;
            vx = 62 * sin(fireInfo.Angle + M_PI / 2);
            vy = 62 * cos(fireInfo.Angle + M_PI / 2);
            x = fireInfo.X + vx / 25;
            y = fireInfo.Y + vy / 25;
            TBullet* bullet = new TBullet(x, y, vx, vy, Epsilon5::Bullet_Type_ARBUZ,
                                          ((TApplication*)(parent()))->GetWorld());
            emit SpawnBullet(bullet);
        }
    } break;
    case Epsilon5::Machinegun: {
        TShootInfo& shootInfo = LastShoots[key];

        if (shootInfo.MachineGunClip == 0 && shootInfo.Time.elapsed() > machinegunReloadTime) {
            shootInfo.MachineGunClip = 30;
            shootInfo.Time.restart();
        }

        if (shootInfo.Time.elapsed() > 100 && shootInfo.MachineGunClip >= 1) {
            double x, y, vx, vy;
            vx = 78 * sin(fireInfo.Angle + M_PI / 2);
            vy = 78 * cos(fireInfo.Angle + M_PI / 2);
            x = fireInfo.X + vx / 25;
            y = fireInfo.Y + vy / 25;
            shootInfo.MachineGunClip--;
            shootInfo.Time.restart();
            TBullet* bullet = new TBullet(x, y, vx, vy, Epsilon5::Bullet_Type_LITTLE_BULLET,
                                          ((TApplication*)(parent()))->GetWorld());
            emit SpawnBullet(bullet);
        }
    } break;
    case Epsilon5::Shotgun: {

        TShootInfo& shootInfo = LastShoots[key];

        if (shootInfo.ShotGunClip == 0 && shootInfo.Time.elapsed() > shotgunReloadTime) {
            shootInfo.ShotGunClip = 8;
            shootInfo.Time.restart();
        }

        if (shootInfo.Time.elapsed() > 900 && shootInfo.ShotGunClip >= 1) {
            double x, y, vx, vy;
            vx = 78 * sin(fireInfo.Angle + M_PI / 2);
            vy = 78 * cos(fireInfo.Angle + M_PI / 2);
            x = fireInfo.X + vx / 25;
            y = fireInfo.Y + vy / 25;
            shootInfo.ShotGunClip--;
            shootInfo.Time.restart();
            for (size_t i = 0; i < 5; i++) {
                TBullet* bullet = new TBullet(x, y, vx + rand()%10, vy + rand()%10, Epsilon5::Bullet_Type_LITTLE_BULLET,
                                              ((TApplication*)(parent()))->GetWorld());
                emit SpawnBullet(bullet);
            }
        }
    } break;
    default:
        break;
    }

}

