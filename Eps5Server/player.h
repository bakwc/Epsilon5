#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    void setId(quint32 id);
    
signals:
    
public slots:

private:
    quint32 _id;
    double _x,_y,_vx,_vy;
    double _angle;
};

#endif // PLAYER_H
