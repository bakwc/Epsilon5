/**
 * @file
 *  Файл с описанием класса Application
 */
#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "maindisplay.h"
#include "network.h"
#include "../Eps5World/world.h"
#include "../Eps5Proto/Epsilon5.pb.h"

/**
 * @brief
 *  Основной класс приложения, отвечает за отображение (mainDisplay),
 * сеть (network), игровой мир (world)
 */
class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int argc, char *argv[]);

    /**
     * @brief
     *  Инициализация - подключение к серверу, включение физики и перерисовки
     * @return
     *  TRUE в случае успешной инициализации
     */
    bool init();

    /**
     * @brief
     * @return
     *  Текущее состояния клавиатуры (нажатые/отпущенные кнопки)
     */
    inline Epsilon5::Control *controlStatus() { return _mainDisplay.controlStatus(); }
private:
    MainDisplay _mainDisplay;
    Network *_network;
    World *_world;
};

#endif // APPLICATION_H
