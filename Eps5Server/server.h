/**
 * @file
 * Файл с описанием класса Server
 */
#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QMap>
#include <QtNetwork/QTcpServer>
#include "client.h"


class Application;

/**
 * @brief
 *  Класс, отвечающий за серверную часть.
 *  Прослушивает порт, обрабатывает новые подключения,
 * добавляет клиентов, пересылает данные.
 */
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    /**
     * @brief
     *  Запускает сервер - начинает слушать порт и ждать подключений клиентов
     * @return
     *  TRUE в случае успеха
     */
    bool start();
signals:
    void newPlayer(quint32 id);
private slots:
    void onClientConnected();
private:
    void timerEvent(QTimerEvent *event);
    /**
     * @brief
     * Рассылает всем подключенным игрокам полное состояние игрового мира
     */
    void sendWorld();
    Application *getParrent();
private:
    QMap<quint32, Client*> _clients;
    QTcpServer *_server;
};

#endif // SERVER_H
