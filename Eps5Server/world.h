#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QMap>
#include "player.h"

class World : public QObject
{
    Q_OBJECT
public:
    explicit World(QObject *parent = 0);
    
signals:
    
public slots:
    void spawnPlayer(quint32 id);
private:
    QMap<quint32, Player*> _players;
};

#endif // WORLD_H
