#include <QtEndian>
#include "application.h"
#include "client.h"
#include "server.h"
#include "player.h"

TServer::TServer(QObject *parent)
    : QObject(parent)
    , Server(new QUdpSocket(this))
    , CurrentId(1)
{
    connect(Server, SIGNAL(readyRead()), SLOT(DataReceived()));
}

bool TServer::Start() {
    if (Server->bind(QHostAddress("0.0.0.0"), 14567))
    {
        this->startTimer(40); // TODO: Remove MN
        return true;
    }
    return false;
}

void TServer::DataReceived() {
    QHostAddress sender;
    quint16 senderPort;
    QByteArray data;
    data.resize(16000);

    qint32 size = Server->readDatagram(data.data(), data.size(), &sender, &senderPort);
    if (size==-1) {
        return;
    }
    data.remove(size,data.size());

    QString addr = sender.toString() + ":" + QString::number(senderPort);
    size_t id;
    if (Ids.find(addr) != Ids.end()) {
        id = Ids[addr];
    } else {
        CurrentId ++;
        if (CurrentId > 100000) {
            CurrentId = 0;
        }
        Ids.insert(addr, CurrentId);
        id = CurrentId;
    }

    auto clientIt = Clients.find(id);
    if (clientIt == Clients.end())
    {       // New client connected
        auto ipIt = Ips.find(sender);
        if (ipIt == Ips.end()) {
            ipIt = Ips.insert(sender, 0);
        }

        if (ipIt.value() >= 2) {
            return;
        }
        ipIt.value()++;

        TClient* client = new TClient(sender, senderPort, id, this);
        connect(client, SIGNAL(SpawnPlayer(size_t)), this, SIGNAL(NewPlayer(size_t)));
        clientIt = Clients.insert(id, client);
    }

    clientIt.value()->OnDataReceived(data);
}

void TServer::timerEvent(QTimerEvent*) {
    DisconnectInactive();
    SendWorld();
}

void TServer::DisconnectInactive() {
    auto i = Clients.begin();
    for (; i != Clients.end();)
    {
        i.value()->EnlargeSeen();
        if (i.value()->GetLastSeen() > 100)
        {
            qDebug() << "Client" << i.value()->GetAddr().toString() << "disconnected";
            auto ipIt = Ips.find(i.value()->GetAddr());
            if (ipIt != Ips.end() && ipIt.value()>0)
                ipIt.value()--;
            emit PlayerDisconnected(i.value()->GetId());
            i.value()->deleteLater();
            i = Clients.erase(i);
        } else {
            i++;
        }
    }
}

void TServer::SendWorld()
{
    QByteArray data=Application()->GetWorld()->Serialize();
    for (auto i = Clients.begin(); i != Clients.end(); i++) {
        i.value()->SendWorld(data);
    }
}

TApplication* TServer::Application() {
    return (TApplication*)(parent());
}

void TServer::Send(const QHostAddress &ip, quint16 port, const QByteArray &data, EPacketType packetType) {
    QByteArray newData;
    quint16 dataSize = qToBigEndian<quint16>(data.size());
    newData += QChar(packetType);
    newData += QByteArray((const char*) &dataSize, sizeof(quint16));
    newData += data;
    Server->writeDatagram(newData, ip, port);
}
