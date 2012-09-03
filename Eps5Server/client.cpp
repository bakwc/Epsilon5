/**
* @file
* Definition of Client
*/
#include <QDebug>
#include "client.h"
#include "server.h"

Client::Client(QObject *parent) :
    QObject(parent),
    _id(0)
{
}

quint32 Client::id()
{
    return _id;
}

void Client::onDataReceived(const QByteArray &data)
{
    Epsilon5::Control control;
    control.ParseFromArray(data.data(),data.size());
    emit controlReceived(control);
}

void Client::send(const QByteArray &data)
{
    getParent()->send(_ip, _port, data);
}

Server *Client::getParent()
{
    return qobject_cast<Server*>(parent());
}
