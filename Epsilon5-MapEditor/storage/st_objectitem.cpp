#include "storage/st_objectitem.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
TObjectItem::TObjectItem()
    : TTItem()
{
}
//------------------------------------------------------------------------------
TObjectItem::TObjectItem(const TObjectItem& object)
    : TTItem(object)
{
}
//------------------------------------------------------------------------------
TObjectItem& TObjectItem::operator =(const TObjectItem& object)
{
    TTItem::operator =(object);
    return *this;
}
//------------------------------------------------------------------------------
quint32 TObjectItem::id() const
{
    return info().id;
}
//------------------------------------------------------------------------------
qint32 TObjectItem::x() const
{
    return info().x;
}
//------------------------------------------------------------------------------
qint32 TObjectItem::y() const
{
    return info().y;
}
//------------------------------------------------------------------------------
QPoint TObjectItem::pos() const
{
    return QPoint(info().x, info().y);
}
//------------------------------------------------------------------------------
qreal TObjectItem::angle() const
{
    return info().angle;
}
//------------------------------------------------------------------------------
void TObjectItem::setId(quint32 id)
{
    info().id = id;
}
//------------------------------------------------------------------------------
void TObjectItem::setPos(const QPoint& pos)
{
    info().x = pos.x();
    info().y = pos.y();
}
//------------------------------------------------------------------------------
void TObjectItem::setX(qint32 x)
{
    info().x = x;
}
//------------------------------------------------------------------------------
void TObjectItem::setY(qint32 y)
{
    info().y = y;
}
//------------------------------------------------------------------------------
void TObjectItem::setAngle(qreal angle)
{
    info().angle = angle;
}
//------------------------------------------------------------------------------
