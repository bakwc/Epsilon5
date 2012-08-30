#include "server.h"
#include <QHostAddress>

Server::Server(QObject *parent) :
    QObject(parent),
    _server(new QTcpServer(this))
{
    connect(_server, SIGNAL(newConnection()), SLOT(onClientConnected()));
}

bool Server::start()
{
    return _server->listen(QHostAddress("0.0.0.0"),1238);
}

void Server::onClientConnected()
{
    Client *client = new Client(this);
    client->setSocket(_server->nextPendingConnection());
    _clients.insert(client->id(),client);
    emit newPlayer(client->id());
}
