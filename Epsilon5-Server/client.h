#pragma once

#include <QObject>
#include <QHostAddress>
#include "../Epslion5-Proto/Epsilon5.pb.h"

class TServer;

class TClient : public QObject
{
    Q_OBJECT
public:
    TClient(const QHostAddress& addr, quint16 port, size_t id, QObject *parent = 0);
    size_t GetId();
    void Send(const QByteArray &data);
    inline quint64 GetLastSeen() {
        return LastSeen;
    }
    void SetSeen();
    void EnlargeSeen();
    inline QHostAddress GetAddr() {
        return Addr;
    }

public slots:
    void OnDataReceived(const QByteArray &data);
signals:
    void ControlReceived(const Epsilon5::Control &control);
private:
    TServer* Server();
private:
    QHostAddress Addr;
    quint16 Port;
    size_t Id;
    quint64 LastSeen;
};
