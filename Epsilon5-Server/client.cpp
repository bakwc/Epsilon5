#include <QtEndian>
#include <QTime>
#include <QDebug>
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
{
}

size_t TClient::GetId() {
    return Id;
}


void TClient::OnDataReceived(const QByteArray &data)
{
    EPacketType packetType;
    quint16 packedDataSize;
    quint16 originDataSize;
    QByteArray content;
    QByteArray receivedPacket = data;
    const int midSize = sizeof(quint16);
    const int posOrigin = sizeof(char);
    const int posPacked = posOrigin + midSize;
    const int posContent = posPacked + midSize;

    try {
        while (receivedPacket.size() > 0) {
            packetType = (EPacketType)(char)(receivedPacket[0]);
            originDataSize = qFromBigEndian<quint16>(
                (const uchar*)receivedPacket.mid(posOrigin, midSize).constData());
            packedDataSize = qFromBigEndian<quint16>(
                (const uchar*)receivedPacket.mid(posPacked, midSize).constData());
            content = qUncompress(receivedPacket.mid(posContent, packedDataSize));

            if( content.isEmpty() && (originDataSize || packedDataSize) )
                throw UException("Wrong packet: cannot unpack data");

            // Retrieve another packet from current.
            // We can receive more than one packet at once
            receivedPacket = receivedPacket.mid(
                packedDataSize + sizeof(char) + 2*midSize);

            switch (packetType) {
            case PT_Control: {
            if (!(PlayerStatus == PS_Spawned || PlayerStatus == PS_Dead)) {
                    throw UException("Player not spawned!");
                }
                Epsilon5::Control control;

                if (control.ParseFromArray(content.data(), content.size())) {
                    size_t currentPacket = control.packet_number();
                    if (control.has_need_full()) {
                        if (control.need_full()) {
                            Server()->NeedFullPacket(Id);
                        }
                    }
                    Server()->Application()->GetWorld()->SetPingForPlayer(Id, currentPacket);
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
                    try {
                        SetSeen();
                        NickName = auth.name().c_str();
                        SendPlayerInfo();

                        QTime dieTime= QTime::currentTime().addSecs(1);
                        while( QTime::currentTime() < dieTime ) {
                            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                        }

                    qDebug() << "Player " << NickName << "("
                             << Addr.toString() << ") connected";

                    Team = rand() % 2 == 1 ? T_One : T_Second; // throw to random team
                    ETeam NewTeam = Server()->AutoBalance();
                    if (NewTeam != T_Neutral) {
                        Team = NewTeam;
                    }

                    emit PlayerConnected();
                    ReSpawn(true);

                    } catch (const std::exception& e){
                    qDebug() << "Exceptiong: " << Q_FUNC_INFO
                             << ": Error spawning player: " << e.what();
                    }
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
    } catch (const UException& e) {
        qDebug() << "Exceptiong: " << Q_FUNC_INFO << ": " << e.what();
    }
}

void TClient::SendWorld(const QByteArray &world) {
    Send(world, PT_World);
}

void TClient::Send(const QByteArray& data, EPacketType packetType)
{
    Server()->Send(Addr, Port, data, packetType);
}

TServer* TClient::Server()
{
    return qobject_cast<TServer*>(parent());
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

void TClient::SetSeen()
{
    LastSeen = 0;
}

void TClient::EnlargeSeen()
{
    LastSeen++;
}

void TClient::ReSpawn(bool newConnected) {

    if (PlayerStatus == PS_Dead || newConnected) {
        ETeam NewTeam = Server()->AutoBalance();
        if (NewTeam != T_Neutral) {
            Team = NewTeam;
        }
        emit SpawnPlayer(Id, Team);
        TPlayer* player = Server()->Application()->GetWorld()->GetPlayer(Id);
        player->SetNickname(NickName);
        connect(this, SIGNAL(ControlReceived(Epsilon5::Control)),
                player, SLOT(ApplyControl(Epsilon5::Control)));
        connect(player, SIGNAL(Death(size_t)),
                this, SLOT(Kill()));
        PlayerStatus = PS_Spawned;
        ((TApplication*)qApp)->GetServer()->NeedFullPacket();
    }
}
