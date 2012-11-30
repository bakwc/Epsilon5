#include "mapitem.h"
#include <QPainter>
#include <QColor>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

MapItem::MapItem(const QSize &size) :
    _size(size)
{
    setFlags(ItemIsSelectable | ItemIsMovable);
}

QRectF MapItem::boundingRect() const
{
    return QRectF(QPointF(0, 0), _size);
}

void MapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    _cPoint = event->pos();
    update();
}

void MapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    _point = event->scenePos();
    setPos(_point - _cPoint);
    QGraphicsItem::mouseMoveEvent(event);
    update();
}

void MapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::black));
    painter->drawRect(QRectF(QPointF(0, 0), _size));
}
