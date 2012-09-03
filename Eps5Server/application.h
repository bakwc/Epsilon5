/**
 * @file
 * Файл с описанием класса Application
 */
#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>
#include "server.h"
#include "../Eps5World/world.h"

class Player;

/**
 * @brief
 * Базовый класс приложения
 */
class Application : public QCoreApplication
{
    Q_OBJECT
public:
    explicit Application(int argc, char *argv[]);
    /**
     * @brief
     *   Инициализация, запускает сервер
     * @return
     *   TRUE в случае успешной инициализации
     */
    bool init();

    /**
     * @brief
     * @return
     *  Полное состояние игрового мира в сериализованном виде
     */
    Epsilon5::World *getSerialisedWorld();

    /**
     * @brief
     * @param id
     *  Идентификатор игрока
     * @return
     *  Игрока с заданным id
     */
    inline Player *getPlayer(quint32 id) { return _world->getPlayer(id); }
signals:

public slots:

private:
    Server *_server;
    World *_world;
};

#endif // APPLICATION_H
