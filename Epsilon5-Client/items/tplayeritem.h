#ifndef TPLAYERITEM_H
#define TPLAYERITEM_H

#include "basicitem.h"

class TPlayerItem : public basic::BasicItem
{
public:
    TPlayerItem(const QSizeF& size = QSizeF(50, 50));

protected:
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TPLAYERITEM_H
