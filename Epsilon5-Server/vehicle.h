#pragma once

#include <QObject>
#include "../utils/umaybe.h"
#include "dynamicobject.h"
#include "player.h"

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
    TVehicleBase* CreateVehicle(size_t id, const TObjectParams& params);
    QPoint GetVehicleSize(size_t id);
private:
    QHash<size_t, TVehicleParams> Vehicles;
};


class TVehicleBase : public TDynamicObject {
    Q_OBJECT
public:
    TVehicleBase(size_t id, const TObjectParams& params, QObject* parent)
        : TDynamicObject(params, parent)
        , Id(id)
    {}
    inline size_t GetId() {
        return Id;
    }
    inline bool HasPlayer() {
        return Player != nullptr;
    }
    inline void SetPlayer(TPlayer* player) {
        if (Player != nullptr) {
            throw UException("Player already in vehicle");
        }
        Player = player;
    }
    inline void RemovePlayer() {
        Player = nullptr;
    }
    inline TPlayer* GetPlayer() {
        Q_ASSERT(Player != nullptr && "Player not exists");
        return Player;
    }
public slots:
    virtual void ApplyControl(const Epsilon5::Control &control) = 0;
    virtual void ApplyCustomPhysics() = 0;
private:
    size_t Id;
    TPlayer* Player = nullptr;
};

class TGroundTransport : public TVehicleBase {
    Q_OBJECT
public:
    TGroundTransport(size_t id, const TObjectParams& params, QObject* parent)
        : TVehicleBase(id, params, parent)
    {}
public slots:
    virtual void ApplyControl(const Epsilon5::Control &control) = 0;
    virtual void ApplyCustomPhysics() = 0;
};

class TGroundTank : public TGroundTransport {
    Q_OBJECT
public:
    TGroundTank(size_t id, const TObjectParams& params, QObject* parent)
        : TGroundTransport(id, params, parent)
    {
        Force.x = 0;
        Force.y = 0;
    }
public slots:
    virtual void ApplyControl(const Epsilon5::Control &control);
    virtual void ApplyCustomPhysics();
private:
    b2Vec2 Force;
    double RotateVelocity;
};

/*
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
