#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QMap>
#include <QtNetwork/QTcpServer>
#include "client.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    bool start();
signals:
    void newPlayer(quint32 id);
private slots:
    void onClientConnected();
private:
    QMap<quint32, Client*> _clients;
    QTcpServer *_server;
};

#endif // SERVER_H
