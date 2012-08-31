#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "maindisplay.h"
#include "network.h"
#include "../Eps5World/world.h"

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int argc, char *argv[]);
    bool init();
private:
    MainDisplay _mainDisplay;
    Network *_network;
    World *_world;
};

#endif // APPLICATION_H
