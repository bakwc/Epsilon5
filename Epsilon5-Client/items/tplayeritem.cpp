#include "tplayeritem.h"
#include <QPainter>
#include <QBrush>

TPlayerItem::TPlayerItem(const QSizeF &size) :
    BasicItem(BasicItem::PLAYER, size)
{
}

void TPlayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const int r = GetSize().width()/2;

    painter->setBrush(Qt::red);
    painter->drawEllipse(r, r, r, r);
}
