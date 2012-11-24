#pragma once

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QHash>

class TApplication;
class TClient;

class TServer : public QObject
{
    Q_OBJECT
public:
    TServer(QObject *parent = 0);
    bool Start();
    void Send(const QHostAddress &ip, quint16 port, const QByteArray &data);
signals:
    void NewPlayer(quint32 id);
    void PlayerDisconnected(quint32 id);
private slots:
    void DataReceived();
private:
    void timerEvent(QTimerEvent *);
    void SendWorld();
    void DisconnectInactive();
    TApplication* Application();
private:
    QHash<QString, size_t> Ids;
    QHash<size_t, TClient*> Clients;
    QHash<QHostAddress, size_t> Ips;
    QUdpSocket* Server;
    size_t CurrentId;
};
