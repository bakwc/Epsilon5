#pragma once

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include "../Epslion5-Proto/Epsilon5.pb.h"

class TApplication;

class TNetwork : public QObject
{
    Q_OBJECT
public:
    explicit TNetwork(QObject *parent = 0);
    const Epsilon5::World& GetWorld() const;
    bool Start();
    inline size_t GetId() { return Id; }
signals:
    void WorldReceived();
private slots:
    void OnDataReceived();
private:
    void SendControls();
    TApplication* Application();
private:
    QUdpSocket* Socket;
    Epsilon5::World World;
    size_t Id;
};
