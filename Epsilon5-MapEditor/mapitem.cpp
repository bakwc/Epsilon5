// mapitem.cpp
#include <QPainter>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QStaticText>
#include "mapitem.h"

TMapItemSignal* TMapItem::mSign = 0;
//------------------------------------------------------------------------------
TMapItem::TMapItem(const utils::TObject& obj, const QPixmap& pix)
    : mObject(obj)
    , mPixmap(pix)
{
    setFlags(ItemIsSelectable | ItemIsMovable);
}
//------------------------------------------------------------------------------
QRectF TMapItem::boundingRect() const
{
    return QRectF(0, 0, mObject.width, mObject.height);
}
//------------------------------------------------------------------------------
void TMapItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mousePressEvent(event);
    mCursorPosition = event->pos();
    update();
    mSign->emitStatus(mObject.name, this->pos(), this->rotation());
}
//------------------------------------------------------------------------------
void TMapItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (mButton == Qt::LeftButton) {
        mScenePosition = event->scenePos() - mCursorPosition;
        setPos(mScenePosition);
        // qDebug() << mScenePosition;
        QGraphicsItem::mouseMoveEvent(event);
    } else if (mButton == Qt::RightButton) {
        mAngle = this->rotation() + event->pos().x() - mCursorPosition.x();
        if (mAngle >= 360) {
            mAngle -= 360;
        }
        this->setRotation(mAngle);
    }
    update();
    mSign->emitStatus(mObject.name, this->pos(), this->rotation());
}
//------------------------------------------------------------------------------
void TMapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
//------------------------------------------------------------------------------
void TMapItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QBrush(Qt::black));
    painter->drawPixmap(0, 0, mPixmap);
}
//------------------------------------------------------------------------------
