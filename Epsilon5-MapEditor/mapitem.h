// mapitem.h
#pragma once
#include <QGraphicsItem>
#include <QPixmap>
#include "utils.h"
//------------------------------------------------------------------------------
class TMapItem : public QGraphicsItem {
public:
    explicit TMapItem(const utils::TObject& obj, const QPixmap& pix);

    QRectF boundingRect() const;
    int id() {
        return mObject.id;
    }
    int posX() {
        return this->x();
    }
    int posY() {
        return this->y();
    }
    int angle() {
        return 0;
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    const utils::TObject& mObject;
    const QPixmap& mPixmap;
    QPointF mScenePosition;
    QPointF mCursorPosition;
};
//------------------------------------------------------------------------------
