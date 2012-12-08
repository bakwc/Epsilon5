#pragma once
#include <QGraphicsPixmapItem>
//------------------------------------------------------------------------------
class TStaticObject : public QGraphicsPixmapItem
{
public:
    TStaticObject(QGraphicsItem* parent = 0);
    TStaticObject(const QPixmap& pixmap, QGraphicsItem* parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    QPointF mCursorPosition;
    Qt::MouseButton mButton;
    int mAngle;
};
//------------------------------------------------------------------------------
