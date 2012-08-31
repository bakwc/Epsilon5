/**
* @file
* Definition of Network
*/
#include <QHostAddress>
#include "network.h"

Network::Network(QObject *parent) :
    QObject(parent),
    _socket(new QTcpSocket(this))
{
    connect(_socket,SIGNAL(readyRead()), SLOT(onReadyRead()));
}

bool Network::start()
{
    _socket->connectToHost(QHostAddress("127.0.0.1"), 1238);
                                            // TODO: Remove HC & MN
    return _socket->waitForConnected(1000);
}

void Network::onReadyRead()
{
    QByteArray data=_socket->readAll();
    emit onDataReceived(data);
}
