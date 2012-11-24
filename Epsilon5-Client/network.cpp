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
    QByteArray data = Socket->readAll();
    if (Id == 0) {
        size_t n = data.indexOf(":");
        QByteArray begin = data.left(n);
        qDebug() << begin;
        Id = begin.toInt();
        data = data.mid(n+1);
        SendControls();
        return;
    }
    World.Clear();
    if (World.ParseFromArray(data.data(),data.size())) {
        emit WorldReceived();
    } else {
        qDebug() << "Error parsing!\n";
    }
    SendControls();
}

TApplication* TNetwork::Application() {
    return (TApplication*)(parent());
}

bool TNetwork::Start() {
    Socket->connectToHost(QHostAddress("193.169.33.254"), 14567);
                                            // TODO: Remove HC & MN
    SendControls();
    return true;
}

void TNetwork::SendControls()
{
    const Epsilon5::Control& control = Application()->GetMainDisplay()->GetControl();
    QByteArray message;
    message.resize(control.ByteSize());
    control.SerializeToArray(message.data(),message.size());
    Socket->write(message);
}
