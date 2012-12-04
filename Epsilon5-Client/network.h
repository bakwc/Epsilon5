#pragma once

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "../Epsilon5-Proto/defines.h"

class TApplication;

class TNetwork : public QObject
{
    Q_OBJECT
public:
    explicit TNetwork(QObject *parent = 0);
    const Epsilon5::World& GetWorld() const;
    void Start();
    inline size_t GetId() { return Id; }
    inline qint64 GetPing() { return Ping; }
    inline bool IsServerAlive() { return IsAlive; }
signals:
    void WorldReceived();
    void LoadMap(QString map);
    void Disconnected();
private slots:
    void OnDataReceived();
    void OnError(QAbstractSocket::SocketError socketError);
    void OnConnected();
private:
    void SendControls();
    void SendPlayerAuth();
    void Send(const QByteArray& data, EPacketType packetType);
    TApplication* Application();
private:
    void timerEvent(QTimerEvent* event);
private:
    QUdpSocket* Socket;
    Epsilon5::World World;
    size_t Id;
    qint64 Ping;
    qint64 LastTime;
    EPlayerStatus Status;
    bool IsAlive;
};
