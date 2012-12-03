#include "basicitem.h"
#include <QPainter>
#include <QBrush>

namespace basic {

QRectF BasicItem::boundingRect() const
{
    return QRectF(QPointF(0, 0), Size);
}

BasicItem::BasicItem() :
    Size(0, 0)
{
}

void BasicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::black));
    painter->drawRect(0, 0, Size.width(), Size.height());
}

}
