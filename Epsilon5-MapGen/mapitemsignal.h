#ifndef MAPITEMSIGNAL_H
#define MAPITEMSIGNAL_H

#include <QObject>
#include <QPointF>

class MapItemSignal : public QObject
{
    Q_OBJECT
public:
    explicit MapItemSignal(QObject *parent = 0);
    void emitStatus(QString name, QPointF itemPos, qreal itemRotation);

signals:
    void mapItemSignal(QString name, QPointF itemPos, qreal itemRotation);
    
};

#endif // MAPITEMSIGNAL_H
