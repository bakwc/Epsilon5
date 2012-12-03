#ifndef BULLET_H
#define BULLET_H

#include "basicitem.h"

class TBulletItem : public basic::BasicItem
{
public:
    TBulletItem(const QSizeF& size = QSizeF(10, 10));

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BULLET_H
