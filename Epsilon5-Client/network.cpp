#include <QtEndian>
#include <QAbstractSocket>
#include "../utils/uexception.h"
#include "maindisplay.h"
#include "application.h"
#include "network.h"

TNetwork::TNetwork(QObject *parent)
    : QObject(parent)
    , Socket(new QUdpSocket(this))
    , Id(0)
{
    connect(Socket, SIGNAL(readyRead()), SLOT(OnDataReceived()));
    connect(Socket, SIGNAL(error(QAbstractSocket::SocketError)),
        SLOT(OnError(QAbstractSocket::SocketError)));
    connect(Socket, SIGNAL(connected()), SLOT(OnConnected()));
    Status = PS_NotConnected;
}

const Epsilon5::World& TNetwork::GetWorld() const {
    return World;
}

void TNetwork::OnDataReceived() {
    qint64 time = QDateTime::currentMSecsSinceEpoch();
    Ping = time - LastTime;
    LastTime = time;
    QByteArray receivedPacket = Socket->readAll();
    EPacketType packetType;
    quint16 packedDataSize;
    quint16 originDataSize;
    QByteArray content;
    QByteArray packed;

    const int midSize = sizeof(quint16);
    const int posOrigin = sizeof(char);
    const int posPacked = posOrigin + midSize;
    const int posContent = posPacked + midSize;

    try {
        while( receivedPacket.size() > 0 )
        {
            packetType = (EPacketType)(char)(receivedPacket[0]);
            originDataSize = qFromBigEndian<quint16>(
                (const uchar*)receivedPacket.mid(posOrigin, midSize).constData());
            packedDataSize = qFromBigEndian<quint16>(
                (const uchar*)receivedPacket.mid(posPacked, midSize).constData());
            packed = receivedPacket.mid(posContent, packedDataSize);
            content = qUncompress(packed);
            if( content.isEmpty() && (originDataSize || packedDataSize) )
                throw UException("Wrong packet: cannot unpack data");

            // Retrieve another packet from current.
            // We can receive more than one packet at once
            receivedPacket = receivedPacket.mid(
                packedDataSize + sizeof(char) + 2*midSize);

            switch (packetType) {
            case PT_PlayerInfo: {
                if (Status != PS_InfoWait) {
                    throw UException("Wrong packet: PT_PlayerInfo");
                }
                Epsilon5::PlayerInfo info;
                if (info.ParseFromArray(content.data(), content.size())) {
                    Id = info.id();
                    QString map = info.map().c_str();
                    emit LoadMap(map);
                    Status = PS_Spawned;
                    //SendControls();
                } else {
                    throw UException("Error parsing player info");
                }
            }
                break;
            case PT_World: {
                if (Status != PS_Spawned) {
                    throw UException("Wrong packet: PT_World");
                }
                World.Clear();
                if (World.ParseFromArray(content.data(), content.size())) {
                    emit WorldReceived();
                    SendControls();
                } else {
                    throw UException("Error parsing world");
                }
            }
                break;
            default:
                throw UException("Unknown packet type");
                break;
            }
        }
    } catch(const std::exception& e) {
        qDebug() << Q_FUNC_INFO << "Exception:" << e.what();
    }
}

void TNetwork::OnError(QAbstractSocket::SocketError socketError)
{
    qDebug() << Q_FUNC_INFO << "Socket error:" << socketError;
    Status = PS_NotConnected;
}

void TNetwork::OnConnected()
{
    SendPlayerAuth();
}

TApplication* TNetwork::Application() {
    return (TApplication*)(parent());
}

void TNetwork::Start() {
    Socket->connectToHost(QHostAddress(
        Application()->GetSettings()->GetServerAddr()),
        Application()->GetSettings()->GetServerPort());
}

void TNetwork::SendControls() {
    const Epsilon5::Control& control = Application()->GetMainDisplay()->GetControl();
    QByteArray message;
    message.resize(control.ByteSize());
    control.SerializeToArray(message.data(),message.size());
    Send(message, PT_Control);
}

void TNetwork::SendPlayerAuth() {
    Epsilon5::Auth auth;
    QByteArray nickName = Application()->GetSettings()->GetNickname().toLocal8Bit();
    auth.set_name(nickName.data(), nickName.size());
    QByteArray data;
    data.resize(auth.ByteSize());
    auth.SerializeToArray(data.data(), data.size());
    Send(data, PT_PlayerAuth);
    Status = PS_InfoWait;
}

// Send packet to the server in form:
// [PACKET_TYPE] [ORIGIN_DATA_SIZE] [DATA]
void TNetwork::Send(const QByteArray& originData, EPacketType packetType) {
    QByteArray sendPacket;
    quint16 originDataSize = qToBigEndian<quint16>(originData.size());
    sendPacket += QChar(packetType);
    sendPacket += QByteArray((const char*) &originDataSize, sizeof(quint16));
    sendPacket += originData;
    Socket->write(sendPacket);
}
