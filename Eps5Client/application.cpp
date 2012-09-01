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
    connect(&_mainDisplay, SIGNAL(requestRedrawObjects()),
            _world, SLOT(requestRedraw()));
    connect(_world, SIGNAL(redraw(DrawableObjects)),
            &_mainDisplay, SLOT(redraw(DrawableObjects)));
    connect(_network, SIGNAL(onDataReceived(QByteArray)),
            _world, SLOT(deSerialize(QByteArray)));
}

bool Application::init()
{
    _mainDisplay.show();
    if (_network->start())
    {
        //_world->start(); No client-side physics by now
        _mainDisplay.start();
        return true;
    }
    return false;
}
