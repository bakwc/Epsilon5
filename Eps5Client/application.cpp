/**
* @file
* Definition of Application
*/
#include "application.h"

Application::Application(int argc, char *argv[]):
    QApplication(argc, argv),
    _network(new Network(this)),
    _world(new World(this))
{
    connect(_world, SIGNAL(redraw(DrawableObjects)),
            &_mainDisplay, SLOT(redraw(DrawableObjects)));
    connect(_network, SIGNAL(onDataReceived(QByteArray)),
            _world, SLOT(deSerialize(QByteArray)));
}

bool Application::init()
{
    _mainDisplay.show();
    return true;
}
