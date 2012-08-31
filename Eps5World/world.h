/**
 * @file
 * Файл с описанием класса World
 */
#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QMap>
#include <QByteArray>
#include "../Eps5World/player.h"

/**
 * @brief Класс World
 * Содержит в себе игровой мир, реализует физику,
 *даёт доступ к игровому миру
 */
class World : public QObject
{
    Q_OBJECT
public:
    explicit World(QObject *parent = 0);

    /**
     * @brief serialize
     * @return
     *  Состояние игрового мира в сериализованном виде
     * Сериализуется с использованием google protobuf
     * @see ../Eps5Proto/Epsilon5.proto
     */
    QByteArray serialize();

    /**
     * @brief start
     *  Запускает физику игрового мира
     */
    void start();
signals:
    
public slots:
    void spawnPlayer(quint32 id);
private:
    void timerEvent(QTimerEvent *event);
private:
    QMap<quint32, Player*> _players;
};

#endif // WORLD_H
