/**
 * @file
 *  Файл с опианием класса Client
 */
#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QHostAddress>
#include "../Eps5Proto/Epsilon5.pb.h"


class Server;

/**
 * @brief
 *  Сетевое взаимодействие с клиентами
 */
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    inline void setIp(QHostAddress addr) { _ip=addr; }
    inline void setPort(quint16 port) { _port=port; }
    inline void setId(quint32 id) { _id=id; }
    void setSeen();
    void enlargeSeen();
    quint32 lastSeen();
    inline QString ip() { return _ip.toString(); }
    inline quint32 ipNum() { return _ip.toIPv4Address(); }

    quint32 id();

    /**
     * @brief
     *  Отправляет данные клиенту через сеть
     * @param data
     *  Данные для отправки
     */
    void send(const QByteArray &data);

    void onDataReceived(const QByteArray &data);

signals:
    void controlReceived(const Epsilon5::Control &control);
private:
    Server *getParent();
private:
    quint32 _id;
    QHostAddress _ip;
    quint16 _port;
    qint64 _lastSeen;
};

#endif // CLIENT_H
