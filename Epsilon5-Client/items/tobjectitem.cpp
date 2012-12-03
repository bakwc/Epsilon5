#include "tobjectitem.h"
#include <QPainter>
#include <QBrush>

TObjectItem::TObjectItem(const QSizeF &size) :
    BasicItem(BasicItem::OBJECT, size)
{

}

void TObjectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::gray);
    painter->drawRect(0, 0, GetSize().width(), GetSize().height());
}
