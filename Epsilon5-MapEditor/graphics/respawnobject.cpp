#include <QPainter>
#include "graphics/respawnobject.h"
//------------------------------------------------------------------------------
const quint8 RADIUS_WIDTH = 2;
//------------------------------------------------------------------------------
TRespawnObject::TRespawnObject(QGraphicsItem *parent)
    : TStaticObject(parent)
{
    setRespawn(true);
}
//------------------------------------------------------------------------------
TRespawnObject::TRespawnObject(const QPixmap &pixmap, QGraphicsItem *parent)
    : TStaticObject(pixmap, parent)
{
    setRespawn(true);
}
//------------------------------------------------------------------------------
QRectF TRespawnObject::boundingRect() const
{
    if( (int)mSpawnRadius * 2 < pixmap().width() )
        return TStaticObject::boundingRect();

    return QRectF(
        pixmap().rect().center().x() - (int)mSpawnRadius - RADIUS_WIDTH * 2,
        pixmap().rect().center().y() - (int)mSpawnRadius - RADIUS_WIDTH * 2,
        (int)mSpawnRadius * 2 + RADIUS_WIDTH * 2,
        (int)mSpawnRadius * 2 + RADIUS_WIDTH * 2);
}
//------------------------------------------------------------------------------
void TRespawnObject::setSpawnRadius(quint32 radius)
{
    mSpawnRadius = radius;
}
//------------------------------------------------------------------------------
quint32 TRespawnObject::spawnRadius() const
{
    return mSpawnRadius;
}
//------------------------------------------------------------------------------
void TRespawnObject::paint(QPainter *painter,
        const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    TStaticObject::paint(painter, option, widget);

    QPen oldPen = painter->pen();
    painter->setPen(QPen(QBrush(Qt::red), RADIUS_WIDTH));
    painter->drawEllipse(pixmap().rect().center(), mSpawnRadius, mSpawnRadius);
    painter->setPen(oldPen);
}
//------------------------------------------------------------------------------
