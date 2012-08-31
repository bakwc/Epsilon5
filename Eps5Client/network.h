/**
 * @file
 *  Файл с описанием класса Network
 */
#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QtNetwork/QTcpSocket>

/**
 * @brief Класс Network
 *  Обеспечивает подключение к серверу, передачу
 * и приём данных
 */
class Network : public QObject
{
    Q_OBJECT
public:
    explicit Network(QObject *parent = 0);

    /**
     * @brief start
     *  Осуществляет подключение к серверу
     * @return
     *  TRUE в случае успешного подключения
     */
    bool start();
    
signals:

    /**
     * @brief onDataReceived
     *  Вызывается как только поступили данные от сервера
     * @param data
     *  Ссылка на поступившие данные
     */
    void onDataReceived(const QByteArray &data);
public slots:
private slots:
    void onReadyRead();
private:
    QTcpSocket *_socket;
};

#endif // NETWORK_H
