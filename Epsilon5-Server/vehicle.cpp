#include <QCoreApplication>

#include "../utils/ucolonsep.h"

#include "vehicle.h"
#include "application.h"

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
            return new TGroundTank(1, params, ((TApplication*)qApp)->GetWorld());
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

void TGroundTank::ApplyControl(const Epsilon5::Control &control) {
    try {
        if (control.keystatus().keydown()) {
            double angle = GetAngle();
            Force(1) = - sin(angle) * 9.0;
            Force(0) = - cos(angle) * 9.0;
        } else if (control.keystatus().keyup()) {
            double angle = GetAngle();
            Force(1) = sin(angle) * 9.0;
            Force(0) = cos(angle) * 9.0;
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

    } catch (const std::exception& e) {
        qDebug() << "TGroundTank::ApplyControl(): " << e.what();
    }
}

void TGroundTank::ApplyCustomPhysics() {
    Body->ApplyLinearImpulse(Force, Body->GetPosition());
    Body->SetAngularVelocity(RotateVelocity);
}
