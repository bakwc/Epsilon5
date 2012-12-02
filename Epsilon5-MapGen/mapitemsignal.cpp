#include "mapitemsignal.h"

MapItemSignal::MapItemSignal(QObject *parent) :
    QObject(parent)
{
}

void MapItemSignal::emitStatus(QString name, QPointF itemPos, qreal itemRotation)
{
    emit mapItemSignal(name, itemPos, itemRotation);
}
