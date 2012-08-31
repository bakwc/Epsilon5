#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    void setId(quint32 id);
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
