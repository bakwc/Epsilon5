#include <QCoreApplication>

#include "../utils/ucolonsep.h"

#include "vehicle.h"
#include "application.h"
#include "defines.h"

TVehicleSpawner::TVehicleSpawner(QObject *parent)
    : QObject(parent)
{
}

void TVehicleSpawner::LoadVehicles(const QString& fileName) {
    UColonSep sep;
    sep.Load(fileName);

    //id:type:width:height:name
    TVehicleParams params;
    for (size_t i = 0; i < sep.Rows(); i++) {
        try {
        params.Id = sep.Get(i, 0);
        params.Size.setX(sep.Get(i, 1));
        params.Size.setY(sep.Get(i, 2));
        params.Type = sep.Get(i, 3);
        Vehicles[params.Id] = params;
        } catch (const UException& e) {
            qDebug() << "Problems with loading: " << fileName;
        }
    }
}

TVehicleBase* TVehicleSpawner::CreateVehicle(size_t id, const TObjectParams& params) {
    switch (id) {
        case 1: {
            TGroundTank* tank = new TGroundTank(1, params, ((TApplication*)qApp)->GetWorld());
            connect(tank, &TGroundTank::Fire, GApp->GetWeaponPacks(), &TWeaponPacks::ActivateWeapon);
            return tank;
        }
    }
    throw UException("Vehicle not found");
}

QPoint TVehicleSpawner::GetVehicleSize(size_t id) {
    if (Vehicles.find(id) == Vehicles.end()) {
        throw UException("Vehicle not found");
    }
    return Vehicles[id].Size;
}

TGroundTank::TGroundTank(size_t id, const TObjectParams& params, QObject* parent)
    : TGroundTransport(id, params, parent)
{
    Force.x = 0;
    Force.y = 0;
    HP = 200;
    WeaponPack = GApp->GetWeaponPacks()->GetPack(1); // TODO: pack number should be passed
}

void TGroundTank::ApplyControl(const Epsilon5::Control &control) {
    try {
        if (control.keystatus().keydown()) {
            qreal angle = GetAngle();
            Force(1) = - sin(angle) * 18.0;
            Force(0) = - cos(angle) * 18.0;
        } else if (control.keystatus().keyup()) {
            qreal angle = GetAngle();
            Force(1) = sin(angle) * 18.0;
            Force(0) = cos(angle) * 18.0;
        } else {
            Force(0) = 0;
            Force(1) = 0;
        }

        if (control.keystatus().keyleft()) {
            RotateVelocity = - 1.0;
        } else if (control.keystatus().keyright()) {
            RotateVelocity = 1.0;
        } else {
            RotateVelocity = 0;
        }

        AimAngle = control.angle();

        if (control.keystatus().keyattack1() ||
                control.keystatus().keyattack2())
        {
            SelectedWeapon = 0;
            if (control.keystatus().keyattack2()) {
                SelectedWeapon = 0;
            }
            emit Fire(this);
        }

    } catch (const std::exception& e) {
        qDebug() << "TGroundTank::ApplyControl(): " << e.what();
    }
}

void TGroundTank::ApplyCustomPhysics() {
    Body->ApplyLinearImpulse(Force, Body->GetPosition());
    Body->SetAngularVelocity(RotateVelocity);
}
