/**
 * @file
 *  Файл с описанием класса Player
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "../Eps5World/dynamicobject.h"
#include "../Eps5Proto/Epsilon5.pb.h"
#include "../Eps5World/bullet.h"

/**
 * @brief
 *  Содержит в себе вектор состояния игрока, а так же
 * различные его параметры
 */
class Player : public DynamicObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);

    inline void setId(quint32 id) { _id=id; }

    inline quint32 id() { return _id; }

    void applyPhysics();
    
signals:
    void spawnBullet(Bullet* bullet);
public slots:
    void applyControl(const Epsilon5::Control &control);
private:
    quint32 _id;
};

#endif // PLAYER_H
