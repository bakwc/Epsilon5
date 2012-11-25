#pragma once

#include <QTime>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "dynamicobject.h"

class TBullet;

class TPlayer : public TDynamicObject
{
    Q_OBJECT
public:
    TPlayer(size_t id, QObject *parent = 0);
    inline size_t GetId() { return Id; }
    void ApplyCustomPhysics();
    void SetNickname(const QString& nickName);
    inline QString GetNickname() {
        return NickName;
    }

signals:
    void SpawnBullet(TBullet*);
public slots:
    void ApplyControl(const Epsilon5::Control &control);
private:
    b2Vec2 Force;
    size_t Id;
    QTime lastShoot;
    QString NickName;
};
