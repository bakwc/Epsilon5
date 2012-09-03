/**
* @file
* Definition of Network
*/
#include <QHostAddress>
#include "network.h"
#include "application.h"
#include "../Eps5Proto/Epsilon5.pb.h"

Network::Network(QObject *parent) :
    QObject(parent),
    _socket(new QUdpSocket(this))
{
    connect(_socket,SIGNAL(readyRead()), SLOT(onReadyRead()));
}

bool Network::start()
{
    _socket->connectToHost(QHostAddress("193.169.33.254"), 1238);
                                            // TODO: Remove HC & MN
    sendControls();
    return true;
}

void Network::onReadyRead()
{
    QByteArray data=_socket->readAll();
    emit onDataReceived(data);
    sendControls();
}

Application *Network::getParrent()
{
    return qobject_cast<Application*>(this->parent());
}

void Network::sendControls()
{
    QByteArray message;
    Epsilon5::Control *control = getParrent()->controlStatus();
    message.resize(control->ByteSize());
    control->SerializeToArray(message.data(),message.size());
    _socket->write(message);
}

