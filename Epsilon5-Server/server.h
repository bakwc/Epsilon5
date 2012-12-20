#pragma once

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QHash>
#include "../Epsilon5-Proto/defines.h"
#include "maps.h"

class TApplication;
class TClient;

class TServer : public QObject
{
    Q_OBJECT
public:
    TServer(QObject *parent = 0);
    void Start();
    void Send(const QHostAddress &ip, quint16 port, const QByteArray &data, EPacketType packetType);
    TApplication* Application();
    void RespawnDeadClients();
    void SerialiseStats(Epsilon5::World& world);
    ETeam AutoBalance();
    void NeedFullPacket(size_t id = -1);
signals:
    void NewPlayer(size_t id, ETeam);
    void PlayerDisconnected(size_t id);
    void PlayerKilled(size_t playerId);
private slots:
    void DataReceived();
private:
    void timerEvent(QTimerEvent *);
    void SendWorld();
    void DisconnectInactive();
private:
    QHash<QString, size_t> Ids;
    QHash<size_t, TClient*> Clients;
    QHash<QHostAddress, size_t> Ips;
    QUdpSocket* Server = new QUdpSocket(this);
    size_t CurrentId = 1;
    size_t LastFullSended = 0;
};
