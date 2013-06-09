#pragma once

#include <QObject>
#include "../utils/umaybe.h"
#include "object.h"
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

class TVehicleBase : public TUnit {
    Q_OBJECT
public:
    TVehicleBase(size_t id, const TObjectParams& params, QObject* parent)
        : TUnit(T_Neutral, params, parent)
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
    virtual size_t GetPlayerId() {
        if (Player == nullptr) {
            return (size_t)-1;
        }
        return Player->GetId();
    }
public slots:
    virtual void ApplyControl(const Epsilon5::Control &control) = 0;
    virtual void ApplyCustomPhysics() = 0;
protected:
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
    TGroundTank(size_t id, const TObjectParams& params, QObject* parent);
signals:
    void Fire(TUnit* unit);
public slots:
    virtual void ApplyControl(const Epsilon5::Control &control);
    virtual void ApplyCustomPhysics();
private:
    b2Vec2 Force;
    qreal RotateVelocity;
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
