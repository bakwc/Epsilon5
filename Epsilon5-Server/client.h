#pragma once

#include <QObject>
#include <QHostAddress>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "../Epsilon5-Proto/defines.h"
#include "maps.h"

class TServer;

class TClient : public QObject
{
    Q_OBJECT
public:
    TClient(const QHostAddress& addr, quint16 port, size_t id, QObject *parent = 0);
    size_t GetId();
    void SendWorld(const QByteArray& world);
    inline quint64 GetLastSeen() {
        return LastSeen;
    }
    void SetSeen();
    void EnlargeSeen();
    inline QHostAddress GetAddr() {
        return Addr;
    }
    void ReSpawn(bool newConnected = false);
    inline QString GetNick() {
        return NickName;
    }
    inline size_t GetScore() {
        return Score;
    }
    inline size_t GetKills() {
        return Kills;
    }
    inline size_t GetDeaths() {
        return Deaths;
    }
public slots:
    void OnDataReceived(const QByteArray &data);
    void Kill() {
        Deaths++;
        PlayerStatus = PS_Dead;
    }
    void Killed(size_t killerId) {
        if (killerId == Id) {
            Kills++;
            Score++;
        }
    }

signals:
    void ControlReceived(const Epsilon5::Control &control);
    void SpawnPlayer(size_t id, ETeam team);
    void PlayerConnected();
private:
    TServer* Server();
    void SendPlayerInfo();
    void Send(const QByteArray& data, EPacketType packetType);
private:
    QHostAddress Addr;
    quint16 Port;
    size_t Id;
    quint64 LastSeen;
    EPlayerStatus PlayerStatus;
    QString NickName;
    ETeam Team;
    size_t Score, Deaths, Kills;
};
