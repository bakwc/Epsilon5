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
    connect(_server, SIGNAL(readyRead()), SLOT(dataReceived()));
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

void Server::dataReceived()
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

    quint32 ip=sender.toIPv4Address();

    quint32 id=ip+senderPort; // TODO: remake without collisions

    auto clientIt = _clients.find(id);  // Search if client exists
    if (clientIt == _clients.end())
    {       // If not = new client connected
        auto ipIt = _ips.find(ip);
        if (ipIt == _ips.end())
            ipIt = _ips.insert(ip, 0);

        if (ipIt.value() >= 2)  // TODO: Remove MN
            return; // Connection rejected

        ipIt.value()++;

        Client *client = new Client(this);
        client->setIp(sender);
        client->setPort(senderPort);
        client->setId(id);
        clientIt = _clients.insert(client->id(),client);
        emit newPlayer(client->id());
        Player *player = getParent()->getPlayer(client->id());
        connect(client, SIGNAL(controlReceived(Epsilon5::Control)),
                player, SLOT(applyControl(Epsilon5::Control)));
    }

    clientIt.value()->onDataReceived(data);
}

void Server::timerEvent(QTimerEvent*)
{
    disconnectInactive();
    sendWorld();
}

void Server::disconnectInactive()
{
    for (auto i=_clients.begin();i!=_clients.end();i++)
    {
        i.value()->enlargeSeen();
        if (i.value()->lastSeen() > 30)
        {
            qDebug() << "Client" << i.value()->ip() << "disconnected";
            auto ipIt = _ips.find(i.value()->ipNum());
            if (ipIt != _ips.end() && ipIt.value()>0)
                ipIt.value()--;
            emit playerDisconnected(i.value()->id());
            i.value()->deleteLater();
            _clients.erase(i);
        }
    }
}

void Server::sendWorld()
{
    Epsilon5::World *world=getParent()->getSerialisedWorld();

    for (auto i=_clients.begin();i!=_clients.end();i++)
    {
        world->set_playerid (i.value()->id());
        QByteArray data;
        data.resize(world->ByteSize());
        world->SerializeToArray(data.data(),data.size());
        i.value()->send(data);
    }
}

Application* Server::getParent()
{
    return (Application*)(parent());
}

void Server::send(const QHostAddress &ip, quint16 port, const QByteArray &data)
{
    _server->writeDatagram(data, ip, port);
}
