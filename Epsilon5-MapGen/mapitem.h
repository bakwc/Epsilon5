#ifndef MAPITEM_H
#define MAPITEM_H

#include <QGraphicsItem>

class MapItem : public QGraphicsItem
{

public:
    explicit MapItem(const QSize &size);

    QRectF boundingRect() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    
signals:
    
public slots:

private:
    QSize _size;
    QPointF _point;

    QPointF _cPoint;
};

#endif // MAPITEM_H
