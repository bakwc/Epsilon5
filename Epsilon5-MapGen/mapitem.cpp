#include "mapitem.h"
#include <QPainter>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


MapItem::MapItem(const QSizeF &size, const QPixmap &pix) :
    _size(size), _pix(pix)
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

    qDebug() << _point;

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
//    painter->drawRect(QRectF(QPointF(0, 0), _size));
    painter->drawPixmap(0, 0, _pix);
}
