#pragma once
#include "graphics/staticobject.h"
//------------------------------------------------------------------------------
class TRespawnObject : public TStaticObject
{
public:
    explicit TRespawnObject(QGraphicsItem* parent = 0);
    TRespawnObject(const QPixmap& pixmap, QGraphicsItem* parent = 0);

    QRectF boundingRect() const;
    void setSpawnRadius(quint32 radius);
    quint32 spawnRadius() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
            QWidget *widget);

private:
    quint32 mSpawnRadius;
};
//------------------------------------------------------------------------------
