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

    /**
     * @brief
     *  Сериализует состояние игрового мира
     * @return
     *  Состояние игрового мира в сериализованном виде
     * Сериализуется с использованием google protobuf
     * @see ../Eps5Proto/Epsilon5.proto
     */
    QByteArray serialize();

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
    void spawnPlayer(quint32 id);
private:
    void timerEvent(QTimerEvent *event);
private:
    QMap<quint32, Player*> _players;
};

#endif // WORLD_H
