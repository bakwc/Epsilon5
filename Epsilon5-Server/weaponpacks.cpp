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
        if (LastShoots[key].elapsed() > 600) {
            LastShoots[key].restart();
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
        if (LastShoots[key].elapsed() > 110) {
            LastShoots[key].restart();
            double x, y, vx, vy;
            vx = 78 * sin(fireInfo.Angle + M_PI / 2);
            vy = 78 * cos(fireInfo.Angle + M_PI / 2);
            x = fireInfo.X + vx / 25;
            y = fireInfo.Y + vy / 25;
            TBullet* bullet = new TBullet(x, y, vx, vy, Epsilon5::Bullet_Type_LITTLE_BULLET,
                                          ((TApplication*)(parent()))->GetWorld());
            emit SpawnBullet(bullet);
        }
    } break;
    case Epsilon5::Shotgun: {
        if (LastShoots[key].elapsed() > 1100) {
            LastShoots[key].restart();
            double x, y, vx, vy;
            vx = 78 * sin(fireInfo.Angle + M_PI / 2);
            vy = 78 * cos(fireInfo.Angle + M_PI / 2);
            x = fireInfo.X + vx / 25;
            y = fireInfo.Y + vy / 25;
            TBullet* bullet = new TBullet(x, y, vx + rand()%10, vy + rand()%10, Epsilon5::Bullet_Type_LITTLE_BULLET,
                                          ((TApplication*)(parent()))->GetWorld());
            emit SpawnBullet(bullet);

            bullet = new TBullet(x, y, vx + rand()%10, vy + rand()%10, Epsilon5::Bullet_Type_LITTLE_BULLET,
                                          ((TApplication*)(parent()))->GetWorld());
            emit SpawnBullet(bullet);

            bullet = new TBullet(x, y, vx + rand()%10, vy + rand()%10, Epsilon5::Bullet_Type_LITTLE_BULLET,
                                          ((TApplication*)(parent()))->GetWorld());
            emit SpawnBullet(bullet);

            bullet = new TBullet(x, y, vx + rand()%10, vy + rand()%10, Epsilon5::Bullet_Type_LITTLE_BULLET,
                                          ((TApplication*)(parent()))->GetWorld());
            emit SpawnBullet(bullet);

            bullet = new TBullet(x, y, vx + rand()%10, vy + rand()%10, Epsilon5::Bullet_Type_LITTLE_BULLET,
                                          ((TApplication*)(parent()))->GetWorld());
            emit SpawnBullet(bullet);
        }
    } break;
    default:
        break;
    }

}
