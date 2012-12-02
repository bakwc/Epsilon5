// mapitem.cpp
#include <QPainter>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "mapitem.h"
//------------------------------------------------------------------------------
TMapItem::TMapItem(const utils::TObject& obj, const QPixmap& pix)
    : mObject(obj)
    , mPixmap(pix) {
    setFlags(ItemIsSelectable | ItemIsMovable);
}
//------------------------------------------------------------------------------
QRectF TMapItem::boundingRect() const {
    return QRectF(0, 0, mObject.width, mObject.height);
}
//------------------------------------------------------------------------------
void TMapItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mousePressEvent(event);
    mCursorPosition = event->pos();
    update();
}
//------------------------------------------------------------------------------
void TMapItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    mScenePosition = event->scenePos();
    setPos(mScenePosition - mCursorPosition);
//    qDebug() << mScenePosition;
    QGraphicsItem::mouseMoveEvent(event);
    update();
}
//------------------------------------------------------------------------------
void TMapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
//------------------------------------------------------------------------------
void TMapItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QBrush(Qt::black));
    painter->drawPixmap(0, 0, mPixmap);
}
//------------------------------------------------------------------------------
