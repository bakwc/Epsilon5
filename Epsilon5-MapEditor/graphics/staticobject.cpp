#include <QDebug>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <qmath.h>
#include "graphics/staticobject.h"
//------------------------------------------------------------------------------
TStaticObject::TStaticObject(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
    , mCursorPosition(QPointF())
    , mFixed(false)
    , mRespawn(false)
{
    setPixmap(QPixmap(32, 32));
    setFlags(ItemIsSelectable | ItemIsMovable);
}
//------------------------------------------------------------------------------
TStaticObject::TStaticObject(const QPixmap& pixmap, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent)
    , mCursorPosition(QPointF())
    , mFixed(false)
    , mRespawn(false)
{
    setPixmap(pixmap);
    setFlags(ItemIsSelectable | ItemIsMovable);
}
//------------------------------------------------------------------------------
QRectF TStaticObject::boundingRect() const
{
    return QRectF(0, 0, pixmap().width(), pixmap().height());
}
//------------------------------------------------------------------------------
void TStaticObject::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (mFixed) {
        return;
    }

    bool fixedAngle = event->modifiers() == Qt::ControlModifier;
    if (mButton == Qt::LeftButton) {
        // Rotate object
        if (event->modifiers() == Qt::ShiftModifier || fixedAngle) {
            int angle = (int)(event->pos().x() - mCursorPosition.x());
            if (!fixedAngle) {
                angle %= 4;
            }
            angle += rotation();
            angle %= 360;

            if (fixedAngle) {
                angle = (int) angle / 45 * 45;
            }

            setTransformOriginPoint(centerPoint());
            setRotation(angle);
            return;
        }

        // Move object
        setTransformOriginPoint(0, 0);
        QGraphicsItem::setPos(mapToScene(
                event->pos().x() - mCursorPosition.x(),
                event->pos().y() - mCursorPosition.y()));
        setTransformOriginPoint(centerPoint());
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
qreal TStaticObject::angleRad()
{
    return rotation() * M_PI / 180;
}
//------------------------------------------------------------------------------
void TStaticObject::setAngle(int grad)
{
    rotateAtCenter(grad);
}
//------------------------------------------------------------------------------
void TStaticObject::setAngle(qreal rad)
{
    rotateAtCenter(rad * 180 / M_PI);
}
//------------------------------------------------------------------------------
void TStaticObject::setPos(qreal x, qreal y)
{
    setTransformOriginPoint(0, 0);
    QGraphicsItem::setPos(x - centerPoint().x(), y - centerPoint().y());
    setTransformOriginPoint(centerPoint());
}
//------------------------------------------------------------------------------
void TStaticObject::setPos(const QPointF &point)
{
    setPos(point.x(), point.y());
}
//------------------------------------------------------------------------------
void TStaticObject::rotateAtCenter(int angle)
{
    setTransformOriginPoint(centerPoint());
    setRotation(angle);
}
//------------------------------------------------------------------------------
QPointF TStaticObject::pos() const
{
    return QGraphicsItem::pos()
        + QPointF(pixmap().width() / 2, pixmap().height() / 2);
}
//------------------------------------------------------------------------------
QPointF TStaticObject::centerPoint() const
{
    return QPointF(pixmap().width() / 2, pixmap().height() / 2);
}
//------------------------------------------------------------------------------
void TStaticObject::setRespawn(bool value)
{
    mRespawn = value;
}
//------------------------------------------------------------------------------
bool TStaticObject::isRespawn() const
{
    return mRespawn;
}
//------------------------------------------------------------------------------
