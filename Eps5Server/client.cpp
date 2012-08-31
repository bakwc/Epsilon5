/**
* @file
* Definition of Client
*/
#include <QDebug>
#include "client.h"

Client::Client(QObject *parent) :
    QObject(parent),
    _socket(NULL),
    _id(0)
{
}

void Client::setSocket(QTcpSocket *socket)
{
    _socket=socket;
    _id=socket->socketDescriptor();
    connect(_socket, SIGNAL(readyRead()), SLOT(onDataReceived()));
}

quint32 Client::id()
{
    return _id;
}

void Client::onDataReceived()
{
    qDebug() << Q_FUNC_INFO;
}

void Client::send(const QByteArray &data)
{
    _socket->write(data);
}
