#include "mapitem.h"
#include <QPainter>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QStaticText>


//MapItem::MapItemSignal *_sign = 0;
MapItemSignal *MapItem::_sign = 0;

MapItem::MapItem(const utils::Object &obj, const QPixmap &pix) :
    _obj(obj), _pix(pix), _angle(0)
{
    setFlags(ItemIsSelectable | ItemIsMovable);
}

QRectF MapItem::boundingRect() const
{
    return QRectF(0, 0, _obj.width, _obj.height);
}

void MapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    _cPoint = event->pos();
    _button = event->button();
    update();

//    qDebug() << Q_FUNC_INFO << event->button();
    _sign->emitStatus(_obj.name, this->pos(), this->rotation());
}

void MapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << Q_FUNC_INFO << event->button();

    if (_button == Qt::LeftButton) {
        _point = event->scenePos() - _cPoint;
        setPos(_point);
        //    qDebug() << _point;
        QGraphicsItem::mouseMoveEvent(event);
    } else if (_button == Qt::RightButton) {
        _angle = this->rotation() + event->pos().x() - _cPoint.x();
        if (_angle >= 360)
            _angle -= 360;

        this->setRotation( _angle);
    }
    update();

    _sign->emitStatus(_obj.name, this->pos(), this->rotation());
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
