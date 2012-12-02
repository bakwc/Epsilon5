#ifndef MAPITEM_H
#define MAPITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include "utils.h"
#include "mapitemsignal.h"

class MapItem : public QGraphicsItem
{
    static MapItemSignal *_sign;

public:
    explicit MapItem(const utils::Object &obj, const QPixmap &pix);

    QRectF boundingRect() const;
    int id() { return _obj.id; }
    int posX() { return this->x(); }
    int posY() { return this->y(); }
    int angle() { return this->rotation(); }

    void setSignalObject(MapItemSignal *s) {
        if (!_sign) _sign = s;
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    const utils::Object &_obj;
    const QPixmap &_pix;
    int _angle;

    Qt::MouseButton _button;
    QPointF _point;
    QPointF _cPoint;
};

#endif // MAPITEM_H
