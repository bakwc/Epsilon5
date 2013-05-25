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

TVehicleBase* TVehicleSpawner::CreateVehicle(size_t id, QPointF pos, double angle) {
    switch (id) {
        case 1: {
        return new TGroundTank(1, pos, angle, ((TApplication*)qApp)->GetWorld());
        }
    }
    throw UException("Object not found");
}

void TGroundTransport::ApplyControl(const Epsilon5::Control &control) {

}


void TGroundTank::ApplyControl(const Epsilon5::Control &control) {

}
