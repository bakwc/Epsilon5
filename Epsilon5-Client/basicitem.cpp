#include "basicitem.h"
#include <QPainter>
#include <QBrush>

namespace basic {

QRectF BasicItem::boundingRect() const
{
    return QRectF(-25, -25, 25, 25);
}

BasicItem::BasicItem()
{
    Size = QSize(50, 50);
}

void BasicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::black));
    painter->drawRect(0, 0, Size.width(), Size.height());
}

}
