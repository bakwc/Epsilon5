#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "graphics/staticobject.h"

TStaticObject::TStaticObject(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
    , mCursorPosition(QPointF(0, 0))
    , mFixed(false)
{
    setPixmap(QPixmap(32, 32));
    setFlags(ItemIsSelectable | ItemIsMovable);
}

TStaticObject::TStaticObject(const QPixmap& pixmap, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent)
    , mCursorPosition(QPointF(0, 0))
    , mFixed(false)
{
    setPixmap(pixmap);
    setFlags(ItemIsSelectable | ItemIsMovable);
}

void TStaticObject::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if( mFixed )
        return;

    if (mButton == Qt::LeftButton && event->modifiers() == Qt::ShiftModifier) {
        mAngle = rotation() + event->pos().x() - mCursorPosition.x();
        mAngle %= 360;
        setTransformOriginPoint(QPoint(pixmap().width() / 2,
                pixmap().height() / 2));
        setRotation(mAngle);
        return;
    }
    if (mButton == Qt::LeftButton) {
        setPos(mapToScene(event->pos().x() - pixmap().width() / 2,
                event->pos().y() - pixmap().height() / 2));
    }
}

void TStaticObject::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    mButton = event->button();
    mCursorPosition = event->pos();
}

void TStaticObject::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    mButton = Qt::NoButton;
}

void TStaticObject::setFixed(bool value)
{
    mFixed = value;
}

//void TStaticObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
//           QWidget *widget)
//{
//    //painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
//    painter->drawPixmap(QPoint(0,0), pixmap());
//    painter->drawEllipse(QPoint(0,0), 10, 10);
//}
