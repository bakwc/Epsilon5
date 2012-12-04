#include <qmath.h>
#include <QDebug>
#include "weaponpacks.h"
#include "application.h"

TWeaponPacks::TWeaponPacks(QObject *parent)
    : QObject(parent)
{
}

void TWeaponPacks::ActivateWeapon(TFireInfo& fireInfo) {
    //EWeaponType weaponType = fireInfo.PrimaryAttack ? WT_Machinegun : WT_Shotgun;
    //qDebug() << Q_FUNC_INFO;
    EWeaponType weaponType = WT_Pistol;

    TTimeKey key;
    key.PlayerId = fireInfo.PlayerId;
    key.WeaponType = weaponType;

    switch (weaponType) {
    case WT_Pistol: {
        if (LastShoots[key].elapsed() > 600) {
            LastShoots[key].restart();
            double x, y, vx, vy;
            vx = 78 * sin(fireInfo.Angle + M_PI / 2);
            vy = 78 * cos(fireInfo.Angle + M_PI / 2);
            x = fireInfo.X + vx / 25;
            y = fireInfo.Y + vy / 25;
            TBullet* bullet = new TBullet(x, y, vx, vy, 12.5, ((TApplication*)(parent()))->GetWorld());
            emit SpawnBullet(bullet);
        }
    }
        break;
    default:
        break;
    }

}
