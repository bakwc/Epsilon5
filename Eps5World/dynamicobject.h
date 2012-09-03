#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include <QObject>
#include "../Eps5Proto/Epsilon5.pb.h"

/**
 * @brief
 *  Содержит в себе вектор состояния
 *движущегося объекта
 */
class DynamicObject : public QObject
{
    Q_OBJECT
public:
    explicit DynamicObject(QObject *parent = 0);

    inline void setX(double x) { _x=x; }
    inline void setY(double y) { _y=y; }
    inline void setVx(double vx) { _vx=vx; }
    inline void setVy(double vy) { _vy=vy; }
    inline void setAngle(double angle) { _angle=angle; }

    inline double x() { return _x; }
    inline double y() { return _y; }
    inline double vx() { return _vx; }
    inline double vy() { return _vy; }
    inline double angle() { return _angle; }

    virtual void applyPhysics()=0;

protected:
    double _x,_y,_vx,_vy;
    double _angle;
};


#endif // DYNAMICOBJECT_H
