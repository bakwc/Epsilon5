#ifndef BASICITEM_H
#define BASICITEM_H

#include <QGraphicsItem>

namespace basic {

class BasicItem : public QGraphicsItem
{
public:
    BasicItem();
    QRectF boundingRect() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QSize Size;
};

}

#endif // BASICITEM_H
