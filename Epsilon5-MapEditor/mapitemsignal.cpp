// mapitemsignal.cpp
#include "mapitemsignal.h"
//------------------------------------------------------------------------------
TMapItemSignal::TMapItemSignal(QObject* parent)
    : QObject(parent) {
}
//------------------------------------------------------------------------------
void TMapItemSignal::emitStatus(QString name, QPointF itemPos,
        qreal itemRotation) {
    emit mapItemSignal(name, itemPos, itemRotation);
}
//------------------------------------------------------------------------------
