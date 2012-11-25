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
}

const Epsilon5::World& TNetwork::GetWorld() const {
    return World;
}

void TNetwork::OnDataReceived() {
    try {
        QByteArray data = Socket->readAll();
        if (data.size() <= 0) {
            throw UException("Empty packet received");
        }
        EPacketType packetType = (EPacketType)(char)(data[0]);
        QByteArray content = data.mid(1);

        switch (packetType) {
        case PT_PlayerInfo: {
            Epsilon5::PlayerInfo info;
            if (info.ParseFromArray(content.data(), content.size())) {
                Id = info.id();
                SendControls();
            } else {
                throw UException("Error parsing player info");
            }
        }
            break;
        case PT_World: {
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
    } catch(const std::exception& e) {
        qDebug() << Q_FUNC_INFO << "Excpetion:" << e.what();
    }
}

TApplication* TNetwork::Application() {
    return (TApplication*)(parent());
}

void TNetwork::Start() {
    Socket->connectToHost(QHostAddress("127.0.0.1"), 14567);
                                            // TODO: Remove HC & MN
    SendPlayerAuth();
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
}

void TNetwork::Send(const QByteArray& data, EPacketType packetType) {
    QByteArray newData;
    newData += QChar(packetType);
    newData += data;
    Socket->write(newData);
}
