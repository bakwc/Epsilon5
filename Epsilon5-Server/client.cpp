#include <QTime>
#include "../utils/uexception.h"
#include "client.h"
#include "server.h"
#include "player.h"
#include "application.h"

TClient::TClient(const QHostAddress& addr,
                 quint16 port, size_t id, QObject *parent)
    : QObject(parent)
    , Addr(addr)
    , Port(port)
    , Id(id)
    , PlayerStatus(PS_AuthWait)
{
}

size_t TClient::GetId() {
    return Id;
}


void TClient::OnDataReceived(const QByteArray &data)
{
    if (data.size() == 0) {
        throw UException("Empty packet!");
    }
    EPacketType packet = (EPacketType)(data[0]);
    QByteArray content = data.mid(1);

    switch (packet) {
    case PT_Control: {
        if (PlayerStatus != PS_Spawned) {
            throw UException("Player not spawned!");
        }
        Epsilon5::Control control;
        if (control.ParseFromArray(content.data(), content.size())) {
            SetSeen();
            emit ControlReceived(control);
        } else {
            throw UException("Parse error: control packet");
        }
    }
        break;
    case PT_PlayerAuth: {
        if (PlayerStatus != PS_AuthWait) {
            throw UException("Player not waiting for auth!");
        }
        Epsilon5::Auth auth;
        if (auth.ParseFromArray(content.data(), content.size())) {
            SetSeen();
            NickName = auth.name().c_str();
            SendPlayerInfo();

            QTime dieTime= QTime::currentTime().addSecs(1);
            while( QTime::currentTime() < dieTime ) {
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            }

            emit SpawnPlayer(Id);
            TPlayer* player = Server()->Application()->GetWorld()->GetPlayer(Id);
            player->SetNickname(NickName);
            connect(this, SIGNAL(ControlReceived(Epsilon5::Control)),
                    player, SLOT(ApplyControl(Epsilon5::Control)));
            PlayerStatus = PS_Spawned;
        } else {
            throw UException("Parse error: auth packet");
        }
    }
        break;
    default:
        throw UException("Unknown packet type!");
        break;
    }
}

void TClient::SendWorld(const QByteArray& world) {
    if (PlayerStatus == PS_Spawned) {
        Send(world, PT_World);
    }
}

void TClient::Send(const QByteArray& data, EPacketType packetType)
{
    Server()->Send(Addr, Port, data, packetType);
}

TServer* TClient::Server()
{
    return qobject_cast<TServer*>(parent());
}

void TClient::SetSeen()
{
    LastSeen = 0;
}

void TClient::EnlargeSeen()
{
    LastSeen++;
}

void TClient::SendPlayerInfo() {
    Epsilon5::PlayerInfo info;
    info.set_id(Id);
    QByteArray map = Server()->Application()->GetMaps()->GetCurrentMap().toLocal8Bit();
    info.set_map(map.data(), map.size());
    QByteArray data;
    data.resize(info.ByteSize());
    info.SerializeToArray(data.data(), data.size());
    Send(data, PT_PlayerInfo);
}
