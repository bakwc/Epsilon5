#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void setSocket(QTcpSocket *socket);
    quint32 id();
signals:
private slots:
    void onDataReceived();
private:
    QTcpSocket *_socket;
    quint32 _id;
};

#endif // CLIENT_H
