#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "graphics/staticobject.h"
//------------------------------------------------------------------------------
TStaticObject::TStaticObject(QGraphicsPixmapItem* parent)
    : QGraphicsPixmapItem(parent)
    , mCursorPosition(QPointF())
    , mFixed(false)
{
    setPixmap(QPixmap(32, 32));
    setFlags(ItemIsSelectable | ItemIsMovable);
}
//------------------------------------------------------------------------------
TStaticObject::TStaticObject(const QPixmap& pixmap, QGraphicsPixmapItem* parent)
    : QGraphicsPixmapItem(pixmap, parent)
    , mCursorPosition(QPointF())
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
        int angle = (rotation() + event->pos().x() - mCursorPosition.x());
        angle %= 360;
        setTransformOriginPoint(QPoint(pixmap().width() / 2,
                pixmap().height() / 2));
        setRotation(angle);
        return;
    }
    if (mButton == Qt::LeftButton) {
        setTransformOriginPoint(0, 0);
        setPos(mapToScene(event->pos().x() - pixmap().width() / 2,
                event->pos().y() - pixmap().height() / 2));
        setTransformOriginPoint(QPoint(pixmap().width() / 2,
                pixmap().height() / 2));
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
