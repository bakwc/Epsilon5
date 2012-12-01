#ifndef MAPITEM_H
#define MAPITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include "utils.h"

class MapItem : public QGraphicsItem
{

public:
    explicit MapItem(const utils::Object &obj, const QPixmap &pix);

    QRectF boundingRect() const;
    int id() { return _obj.id; }
    int posX() { return this->x(); }
    int posY() { return this->y(); }
    int angle() { return 0; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    
signals:
    
public slots:

private:
    const utils::Object &_obj;
    const QPixmap &_pix;

    QPointF _point;

    QPointF _cPoint;
};

#endif // MAPITEM_H
