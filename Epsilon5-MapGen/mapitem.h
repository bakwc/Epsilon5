#ifndef MAPITEM_H
#define MAPITEM_H

#include <QGraphicsItem>
#include <QPixmap>

class MapItem : public QGraphicsItem
{

public:
    explicit MapItem(const QSizeF &size, const QPixmap &pix);

    QRectF boundingRect() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    
signals:
    
public slots:

private:
    QSizeF _size;
    QPointF _point;
    QPixmap _pix;

    QPointF _cPoint;
};

#endif // MAPITEM_H
