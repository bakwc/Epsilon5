/**
* @file
* Definition of Server
*/
#include "server.h"
#include "application.h"
#include <QHostAddress>

Server::Server(QObject *parent) :
    QObject(parent),
    _server(new QTcpServer(this))
{
    connect(_server, SIGNAL(newConnection()), SLOT(onClientConnected()));
}

bool Server::start()
{
    if (_server->listen(QHostAddress("0.0.0.0"),1238))
    {
        this->startTimer(20); // TODO: Remove MN
        return true;
    }
    return false;
}

void Server::onClientConnected()
{
    qDebug() << Q_FUNC_INFO;
    Client *client = new Client(this);
    client->setSocket(_server->nextPendingConnection());
    _clients.insert(client->id(),client);
    emit newPlayer(client->id());
}

void Server::timerEvent(QTimerEvent *event)
{
    sendWorld();
}

void Server::sendWorld()
{
    QByteArray world=getParrent()->getSerialisedWorld();

    for (auto i=_clients.begin();i!=_clients.end();i++)
        i.value()->send(world);
    //TODO: Send world to clients
}

Application* Server::getParrent()
{
    return (Application*)(parent());
}
