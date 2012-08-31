/**
 * @file
 *  Файл с опианием класса Client
 */
#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>

/**
 * @brief Класс Client
 *  Сетевое взаимодействие с клиентами
 */
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    /**
     * @brief setSocket
     *  Устанавливает сокет
     * @param socket
     *  Сокет, через который будет идти связь
     */
    void setSocket(QTcpSocket *socket);

    quint32 id();

    /**
     * @brief send
     *  Отправляет данные клиенту через сеть
     * @param data
     *  Данные для отправки
     */
    void send(const QByteArray &data);

signals:
private slots:
    void onDataReceived();
private:
    QTcpSocket *_socket;
    quint32 _id;
};

#endif // CLIENT_H
