/**
 * @file
 *  Файл с описанием класса Player
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

/**
 * @brief Класс Player
 *  Содержит в себе вектор состояния игрока, а так же
 * различные его параметры
 */
class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);

    inline void setId(quint32 id) { _id=id; }
    inline void setX(quint32 x) { _x=x; }
    inline void setY(quint32 y) { _y=y; }
    inline void setVx(quint32 vx) { _vx=vx; }
    inline void setVy(quint32 vy) { _vy=vy; }
    inline void setAngle(quint32 angle) { _angle=angle; }

    inline quint32 id() { return _id; }
    inline double x() { return _x; }
    inline double y() { return _y; }
    inline double vx() { return _vx; }
    inline double vy() { return _vy; }
    inline double angle() { return _angle; }
    
signals:
    
public slots:

private:
    quint32 _id;
    double _x,_y,_vx,_vy;
    double _angle;
};

#endif // PLAYER_H
