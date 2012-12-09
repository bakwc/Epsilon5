#pragma once
#include <QGraphicsPixmapItem>
//------------------------------------------------------------------------------
class TStaticObject : public QGraphicsPixmapItem
{
public:
    TStaticObject(QGraphicsItem* parent = 0);
    TStaticObject(const QPixmap& pixmap, QGraphicsItem* parent = 0);
    void setFixed(bool value = true);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
//               QWidget *widget);

private:
    QPointF mCursorPosition;
    Qt::MouseButton mButton;
    int mAngle;
    bool mFixed;
};
//------------------------------------------------------------------------------
