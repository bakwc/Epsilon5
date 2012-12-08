#include "storage/st_mapitem.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
TMapItem::TMapItem()
{
}
//------------------------------------------------------------------------------
TMapItem::TMapItem(const TMapItem& map)
    : TTItem(map)
{
}
//------------------------------------------------------------------------------
TMapItem& TMapItem::operator =(const TMapItem& map)
{
    TTItem::operator =(map);
    mObjects = map.mObjects;
    mRespawns = map.mRespawns;
    return *this;
}
//------------------------------------------------------------------------------
QString TMapItem::name() const
{
    return info().name;
}
//------------------------------------------------------------------------------
QSize TMapItem::size() const
{
    return QSize(info().width, info().height);
}
//------------------------------------------------------------------------------
quint32 TMapItem::width() const
{
    return info().width;
}
//------------------------------------------------------------------------------
quint32 TMapItem::height() const
{
    return info().height;
}
//------------------------------------------------------------------------------
void TMapItem::setName(const QString& name)
{
    info().name = name;
}
//------------------------------------------------------------------------------
void TMapItem::setSize(quint32 width, quint32 height)
{
    info().width = width;
    info().height = height;
}
//------------------------------------------------------------------------------
void TMapItem::setSize(const QSize& size)
{
    info().width = size.width();
    info().height = size.height();
}
//------------------------------------------------------------------------------
