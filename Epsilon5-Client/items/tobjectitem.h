#ifndef TOBJECTITEM_H
#define TOBJECTITEM_H

#include "basicitem.h"

class TObjectItem : public basic::BasicItem
{
public:
    TObjectItem(const QSizeF& size = QSizeF(100, 100));

protected:
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TOBJECTITEM_H
