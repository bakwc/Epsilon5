#include <QGraphicsSceneMouseEvent>
#include "staticobject.h"

TStaticObject::TStaticObject(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
    , mCursorPosition(QPointF(0,0))
{
    setPixmap(QPixmap(32,32));
    setFlags(ItemIsSelectable | ItemIsMovable);
}

TStaticObject::TStaticObject(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent)
    , mCursorPosition(QPointF(0,0))
{
    setPixmap(pixmap);
    setFlags(ItemIsSelectable | ItemIsMovable);
}

void TStaticObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if( mButton == Qt::LeftButton && event->modifiers() == Qt::ShiftModifier )
    {
        mAngle = rotation() + event->pos().x() - mCursorPosition.x();
        mAngle %= 360;
//        setTransformOriginPoint(QPoint(pos().x() + pixmap().width()/2,
//            pos().y() + pixmap().height()/2));
        setTransformOriginPoint(QPoint(pixmap().width()/2,
            pixmap().height()/2));
        setRotation(mAngle);
//        resetTransform();
        return;
    }
    if( mButton == Qt::LeftButton )
    {
        setPos(mapToScene(event->pos().x() - pixmap().width() / 2,
                event->pos().y() - pixmap().height() / 2));
    }
}

void TStaticObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mButton = event->button();
    mCursorPosition = event->pos();
}

void TStaticObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    mButton = Qt::NoButton;
}
