#include "client.h"
#include "server.h"

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
    Epsilon5::Control control;
    if (control.ParseFromArray(data.data(),data.size()))
    {
        SetSeen();
        emit ControlReceived(control);
    }
}

void TClient::Send(const QByteArray &data)
{
    Server()->Send(Addr, Port, data);
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
