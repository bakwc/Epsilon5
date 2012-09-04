#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include "../Eps5World/dynamicobject.h"
#include "../Eps5Proto/Epsilon5.pb.h"

/**
 * @brief
 *  Содержит в себе вектор состояния пули
 */
class Bullet : public DynamicObject
{
    Q_OBJECT
public:
    explicit Bullet(QObject *parent = 0);

    inline void setDamage(double damage) { _damage=damage; }

    inline double damage() { return _damage; }
    inline qint32 ttl() { return _ttl; }

    void applyPhysics();

private:
    double _damage;
    double _x,_y,_vx,_vy;
    qint32 _ttl;
    double _angle;
};


#endif // BULLET_H


