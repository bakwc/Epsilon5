#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "graphics/staticobject.h"
//------------------------------------------------------------------------------
TStaticObject::TStaticObject(QGraphicsPixmapItem* parent)
    : QGraphicsPixmapItem(parent)
    , mCursorPosition(QPointF(0, 0))
    , mFixed(false)
{
    setPixmap(QPixmap(32, 32));
    setFlags(ItemIsSelectable | ItemIsMovable);
}
//------------------------------------------------------------------------------
TStaticObject::TStaticObject(const QPixmap& pixmap, QGraphicsPixmapItem* parent)
    : QGraphicsPixmapItem(pixmap, parent)
    , mCursorPosition(QPointF(0, 0))
    , mFixed(false)
{
    setPixmap(pixmap);
    setFlags(ItemIsSelectable | ItemIsMovable);
}
//------------------------------------------------------------------------------
QRectF TStaticObject::boundingRect()
{
    return QRectF(0, 0, pixmap().width(), pixmap().height());
}
//------------------------------------------------------------------------------
void TStaticObject::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (mFixed) {
        return;
    }

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
//        qDebug( "item pos: %fx%f", pos().x(), pos().y() );
    }
}
//------------------------------------------------------------------------------
void TStaticObject::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    mButton = event->button();
    mCursorPosition = event->pos();
}
//------------------------------------------------------------------------------
void TStaticObject::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    mButton = Qt::NoButton;
}
//------------------------------------------------------------------------------
void TStaticObject::setFixed(bool value)
{
    mFixed = value;
}
//------------------------------------------------------------------------------
void TStaticObject::setObjectId(quint32 id)
{
    mObjectId = id;
}
//------------------------------------------------------------------------------
quint32 TStaticObject::objectId()
{
    return mObjectId;
}
//------------------------------------------------------------------------------
