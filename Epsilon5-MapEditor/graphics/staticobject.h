#pragma once
#include <QGraphicsPixmapItem>
//------------------------------------------------------------------------------
class TStaticObject : public QGraphicsPixmapItem
{
public:
    explicit TStaticObject(QGraphicsPixmapItem* parent = 0);
    TStaticObject(const QPixmap& pixmap, QGraphicsPixmapItem* parent = 0);
    void setFixed(bool value = true);
    QRectF boundingRect();
    quint32 objectId();
    void setObjectId(quint32 id);
    void setAngle(qreal rad);
    void setAngle(int grad);
    qreal angleRad();
    void setPos(qreal x, qreal y);
    void setPos(const QPointF& point);
    QPointF pos() const;
    void setRespawn(bool value);
    bool isRespawn() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    void rotateAtCenter(int angle);
    QPointF centerPoint() const;

private:
    QPointF mCursorPosition;
    Qt::MouseButton mButton;
    bool mFixed;
    quint32 mObjectId;
    bool mRespawn;
};
//------------------------------------------------------------------------------
