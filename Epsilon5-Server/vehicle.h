#pragma once

#include <QObject>

#include "dynamicobject.h"

class TVehicleBase;

struct TVehicleParams {
    QPoint Size;
    size_t Id;
    size_t Type;
};

class TVehicleSpawner : public QObject
{
    Q_OBJECT
public:
    explicit TVehicleSpawner(QObject *parent = 0);
    void LoadVehicles(const QString& fileName);
    TVehicleBase* CreateVehicle(size_t id);
private:
    QHash<size_t, TVehicleParams> Vehicles;
};


class TVehicleBase : public TDynamicObject {
    Q_OBJECT
public slots:
    virtual void ApplyControl(const Epsilon5::Control &control) = 0;
};

class TGroundTransport : public TVehicleBase {
    Q_OBJECT
public slots:
    void ApplyControl(const Epsilon5::Control &control);
};

/*
class TGroundTank : public TGroundTransport {
    Q_OBJECT
public slots:
    void ApplyControl(const Epsilon5::Control &control);
};

class TSpaceTransport : public TVehicleBase {
    Q_OBJECT
public slots:
    void ApplyControl(const Epsilon5::Control &control);
};

class TDeathStar : public TSpaceTransport {
    Q_OBJECT
public slots:
    void ApplyControl(const Epsilon5::Control &control);
};
*/
