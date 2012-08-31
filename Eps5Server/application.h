/**
 * @file
 * Файл с описанием класса Application
 */
#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>
#include "server.h"
#include "../Eps5World/world.h"

/**
 * @brief Класс Application
 * Базовый класс приложения
 */
class Application : public QCoreApplication
{
    Q_OBJECT
public:
    explicit Application(int argc, char *argv[]);
    /**
     * @brief init
     *   Инициализация, запускает сервер
     * @return
     *   TRUE в случае успешной инициализации
     */
    bool init();
    /**
     * @brief getSerialisedWorld
     * @return
     *  Полное состояние игрового мира в сериализованном виде
     */
    QByteArray getSerialisedWorld();
signals:

public slots:

private:
    Server *_server;
    World *_world;
};

#endif // APPLICATION_H
