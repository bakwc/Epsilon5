#pragma once

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "../Epsilon5-Proto/defines.h"

class TApplication;

class TNetwork : public QObject {
    Q_OBJECT
public:
    explicit TNetwork(QObject* parent = 0);
    const Epsilon5::World& GetWorld() const;
    void Start();
    inline size_t GetId() {
        return Id;
    }
signals:
    void WorldReceived();
    void LoadMap(QString map);
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
    QUdpSocket* Socket;
    Epsilon5::World World;
    size_t Id;
    EPlayerStatus Status;
};
