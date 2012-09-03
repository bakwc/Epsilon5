/**
* @file
* Definition of Server
*/
#include "server.h"
#include "application.h"
#include <QHostAddress>
#include "../Eps5World/player.h"

Server::Server(QObject *parent) :
    QObject(parent),
    _server(new QUdpSocket(this))
{
    //connect(_server, SIGNAL(newConnection()), SLOT(onClientConnected()));
    connect(_server, SIGNAL(readyRead()), SLOT(onSomethingReceived()));
}

bool Server::start()
{
    if (_server->bind(QHostAddress("0.0.0.0"),1238))
    {
        this->startTimer(10); // TODO: Remove MN
        return true;
    }
    return false;
}

void Server::onSomethingReceived()
{
    QHostAddress sender;
    quint16 senderPort;
    QByteArray data;
    data.resize(16000);

    qint32 size = _server->readDatagram(    // Read data
                data.data(), data.size(), &sender, &senderPort);
    if (size==-1)
        return;
    data.remove(size,data.size());

    quint32 id=sender.toIPv4Address()+senderPort; // TODO: remake without collisions

    auto clientIt = _clients.find(id);  // Search if client exists
    if (clientIt == _clients.end())
    {       // If not = new client connected
        Client *client = new Client(this);
        client->setIp(sender);
        client->setPort(senderPort);
        client->setId(id);
        clientIt = _clients.insert(client->id(),client);
        emit newPlayer(client->id());
        Player *player = getParrent()->getPlayer(client->id());
        connect(client, SIGNAL(controlReceived(Epsilon5::Control)),
                player, SLOT(applyControl(Epsilon5::Control)));
    }

    clientIt.value()->onDataReceived(data);
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
}

Application* Server::getParrent()
{
    return (Application*)(parent());
}

void Server::send(const QHostAddress &ip, quint16 port, const QByteArray &data)
{
    _server->writeDatagram(data, ip, port);
}
