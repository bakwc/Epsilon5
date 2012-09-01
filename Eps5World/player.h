/**
 * @file
 *  Файл с описанием класса Player
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

/**
 * @brief
 *  Содержит в себе вектор состояния игрока, а так же
 * различные его параметры
 */
class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);

    inline void setId(quint32 id) { _id=id; }
    inline void setX(double x) { _x=x; }
    inline void setY(double y) { _y=y; }
    inline void setVx(double vx) { _vx=vx; }
    inline void setVy(double vy) { _vy=vy; }
    inline void setAngle(double angle) { _angle=angle; }

    inline quint32 id() { return _id; }
    inline double x() { return _x; }
    inline double y() { return _y; }
    inline double vx() { return _vx; }
    inline double vy() { return _vy; }
    inline double angle() { return _angle; }

    void applyPhysics();
    
signals:
    
public slots:

private:
    quint32 _id;
    double _x,_y,_vx,_vy;
    double _angle;
};

#endif // PLAYER_H
