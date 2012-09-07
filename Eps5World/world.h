/**
 * @file
 * Файл с описанием класса World
 */
#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QMap>
#include <QByteArray>
#include <QList>
#include <Box2D/Box2D.h>
#include "../Eps5Proto/Epsilon5.pb.h"
#include "../Eps5World/player.h"
#include "../Eps5World/bullet.h"
#include "../Eps5World/drawableObject.h"

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
    ~World();

    /**
     * @brief
     *  Сериализует состояние игрового мира
     * @return
     *  Состояние игрового мира в сериализованном виде
     * Сериализуется с использованием google protobuf
     * @see ../Eps5Proto/Epsilon5.proto
     */
    Epsilon5::World* serialize();

    /**
     * @brief
     *  Запускает физику игрового мира
     */
    void start();

    /**
     * @brief
     * @param id
     *  Идентификатор игрока
     * @return
     *  Игрока с заданным id
     */
    Player *getPlayer(quint32 id);

    inline quint32 selfId() { return _selfId; }
signals:

    /**
     * @brief
     *  Сигнал вызывается, когда движку необходимо перерисовать мир
     * @param
     *  Ссылка на список объектов, которые необходимо отрисовать
     */
    void redraw(const DrawableObjects &objects);
public slots:

    /**
     * @brief
     *  Готовит список объектов для отрисовки и вызывает сигнал redraw
     */
    void requestRedraw();

    /**
     * @brief
     *  Восстанавливает состояние игрового мира
     * @param data
     *  Массив байт, из которого происходит восстановление
     */
    void deSerialize(const QByteArray &data);

    /**
     * @brief
     *  Добавляет в игровой мир игрока
     * @param id
     *  Идентификатор игрока
     */
    void playerEnter(quint32 id);

    void playerExit(quint32 id);

    void spawnBullet(Bullet *bullet);
private:
    void timerEvent(QTimerEvent *event);
private:
    QMap<quint32, Player*> _players;
    QList<Bullet*> _bullets;
    Epsilon5::World *_worldState;
    quint32 _selfId;
    b2World *_b2world;
};

#endif // WORLD_H
