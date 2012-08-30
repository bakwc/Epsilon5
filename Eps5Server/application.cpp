#include "application.h"

Application::Application(int argc, char *argv[]) :
    QCoreApplication(argc, argv),
    _server(new Server(this)),
    _world(new World(this))
{
    connect(_server,SIGNAL(newPlayer(quint32)),
            _world,SLOT(spawnPlayer(quint32)));
}

bool Application::init()
{
    return _server->start();
}
