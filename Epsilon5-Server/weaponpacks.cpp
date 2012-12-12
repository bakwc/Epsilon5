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

        if (shootInfo.PistolClips == 0)
        {
            break;
        }

        if (shootInfo.PistolAmmoInClip == 0 && shootInfo.Time.elapsed() > pistolReloadTime) {
            shootInfo.PistolAmmoInClip = 12;
            shootInfo.PistolClips--;
            shootInfo.Time.restart();
        }

        if (shootInfo.Time.elapsed() > 400 && shootInfo.PistolAmmoInClip>= 1) {
            shootInfo.Time.restart();
            double x, y, vx, vy;
            vx = 62 * sin(fireInfo.Angle + M_PI / 2);
            vy = 62 * cos(fireInfo.Angle + M_PI / 2);
            x = fireInfo.X + vx / 25;
            y = fireInfo.Y + vy / 25;
            shootInfo.PistolAmmoInClip--;
            shootInfo.Time.restart();
            TBullet* bullet = new TBullet(x, y, vx, vy, Epsilon5::Bullet_Type_ARBUZ,
                                          fireInfo.PlayerId,
                                          ((TApplication*)(parent()))->GetWorld());
            emit SpawnBullet(bullet);
        }
    } break;
    case Epsilon5::Machinegun: {
        TShootInfo& shootInfo = LastShoots[key];

        //Check weapon clips
        if (shootInfo.MachineGunClips == 0) {
            break;
        }

        //Control our bullets and clips
        if (shootInfo.MachineGunAmmoInClip == 0 && shootInfo.Time.elapsed() > machinegunReloadTime) {
            shootInfo.MachineGunAmmoInClip = 30;
            shootInfo.MachineGunClips--;
            shootInfo.Time.restart();
        }

        //Per shot delay
        if (shootInfo.Time.elapsed() > 100 && shootInfo.MachineGunAmmoInClip >= 1) {
            double x, y, vx, vy;
            vx = 78 * sin(fireInfo.Angle + M_PI / 2);
            vy = 78 * cos(fireInfo.Angle + M_PI / 2);
            x = fireInfo.X + vx / 25;
            y = fireInfo.Y + vy / 25;
            shootInfo.MachineGunAmmoInClip--;
            shootInfo.Time.restart();
            TBullet* bullet = new TBullet(x, y, vx, vy, Epsilon5::Bullet_Type_LITTLE_BULLET,
                                          fireInfo.PlayerId,
                                          ((TApplication*)(parent()))->GetWorld());
            emit SpawnBullet(bullet);
        }
    } break;
    case Epsilon5::Shotgun: {

        TShootInfo& shootInfo = LastShoots[key];

        if (shootInfo.ShotGunClips == 0) {
            break;
        }

        if (shootInfo.ShotGunAmmoInClip == 0 && shootInfo.Time.elapsed() > shotgunReloadTime) {
            shootInfo.ShotGunAmmoInClip = 8;
            shootInfo.ShotGunClips--;
            shootInfo.Time.restart();
        }

        if (shootInfo.Time.elapsed() > 900 && shootInfo.ShotGunAmmoInClip >= 1) {
            double x, y, vx, vy;
            vx = 98 * sin(fireInfo.Angle + M_PI / 2);
            vy = 98 * cos(fireInfo.Angle + M_PI / 2);
            x = fireInfo.X + vx / 25;
            y = fireInfo.Y + vy / 25;
            shootInfo.ShotGunAmmoInClip--;
            shootInfo.Time.restart();
            for (size_t i = 0; i < 5; i++) {
                TBullet* bullet = new TBullet(x, y, vx + rand()%10, vy + rand()%10,
                                              Epsilon5::Bullet_Type_LITTLE_BULLET,
                                              fireInfo.PlayerId,
                                              ((TApplication*)(parent()))->GetWorld());
                emit SpawnBullet(bullet);
            }
        }
    } break;
    default:
        break;
    }

}


