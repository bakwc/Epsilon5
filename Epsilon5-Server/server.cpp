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
            if (data.indexOf(":") == -1) {
                return;
            }
            ipIt = Ips.insert(sender, 0);
        }

        if (ipIt.value() >= 2) {
            return;
        }
        ipIt.value()++;

        QString nickName = data.left(data.indexOf(":"));

        TClient* client = new TClient(sender, senderPort, id, this);

        QByteArray dataId = QString(QString::number(id)+":").toLocal8Bit();
        client->Send(dataId);

        clientIt = Clients.insert(id, client);
        emit NewPlayer(id);
        TPlayer *player = Application()->GetWorld()->GetPlayer(id);
        player->SetNickname(nickName);
        connect(client, SIGNAL(ControlReceived(Epsilon5::Control)),
                player, SLOT(ApplyControl(Epsilon5::Control)));
        return;
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
        if (i.value()->GetLastSeen() > 30)
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
        i.value()->Send(data);
    }
}

TApplication* TServer::Application() {
    return (TApplication*)(parent());
}

void TServer::Send(const QHostAddress &ip, quint16 port, const QByteArray &data) {
    Server->writeDatagram(data, ip, port);
}
