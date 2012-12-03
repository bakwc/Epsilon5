#include "tbulletitem.h"
#include <QPainter>
#include <QBrush>


TBulletItem::TBulletItem(const QSizeF &size) :
    BasicItem(BasicItem::BULLET, size)
{
}

void TBulletItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const int r = GetSize().width()/2;

    painter->setBrush(Qt::green);
    painter->drawEllipse(r, r, r, r);
}


