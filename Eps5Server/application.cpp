/**
* @file
* Definition of Application
*/
#include "application.h"

Application::Application(int argc, char *argv[]) :
    QCoreApplication(argc, argv),
    _server(new Server(this)),
    _world(new World(this))
{
    connect(_server, SIGNAL(newPlayer(quint32)),
            _world, SLOT(playerEnter(quint32)));

    connect(_server, SIGNAL(playerDisconnected(quint32)),
            _world, SLOT(playerExit(quint32)));
}

bool Application::init()
{
    if (_server->start())
    {
        _world->start();
        return true;
    }
    return false;
}

Epsilon5::World* Application::getSerialisedWorld()
{
    return _world->serialize();
}
