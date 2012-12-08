#include "storage/st_respawnitem.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
TRespawnItem::TRespawnItem()
    : TTItem()
{
}
//------------------------------------------------------------------------------
TRespawnItem::TRespawnItem(const TRespawnItem& respawn)
    : TTItem(respawn)
{
}
//------------------------------------------------------------------------------
TRespawnItem& TRespawnItem::operator =(const TRespawnItem& respawn)
{
    TTItem::operator =(respawn);
    return *this;
}
//------------------------------------------------------------------------------
quint32 TRespawnItem::x() const
{
    return info().x;
}
//------------------------------------------------------------------------------
quint32 TRespawnItem::y() const
{
    return info().y;
}
//------------------------------------------------------------------------------
QPoint TRespawnItem::pos() const
{
    return QPoint(info().x, info().y);
}
//------------------------------------------------------------------------------
quint32 TRespawnItem::captureRadius() const
{
    return info().captureRadius;
}
//------------------------------------------------------------------------------
quint32 TRespawnItem::spawnRadius() const
{
    return info().spawnRadius;
}
//------------------------------------------------------------------------------
bool TRespawnItem::isCapturable() const
{
    return info().isCapturable;
}
//------------------------------------------------------------------------------
bool TRespawnItem::isMain() const
{
    return info().isMain;
}
//------------------------------------------------------------------------------
quint32 TRespawnItem::captureTime() const
{
    return info().captureTime;
}
//------------------------------------------------------------------------------
ETeam TRespawnItem::team() const
{
    return info().team;
}
//------------------------------------------------------------------------------
void TRespawnItem::setX(quint32 x)
{
    info().x = x;
}
//------------------------------------------------------------------------------
void TRespawnItem::setY(quint32 y)
{
    info().y = y;
}
//------------------------------------------------------------------------------
void TRespawnItem::setPos(const QPoint& pos)
{
    info().x = pos.x();
}
//------------------------------------------------------------------------------
void TRespawnItem::setCaptureRadius(quint32 radius)
{
    info().captureRadius = radius;
}
//------------------------------------------------------------------------------
void TRespawnItem::setSpawnRadius(quint32 radius)
{
    info().spawnRadius = radius;
}
//------------------------------------------------------------------------------
void TRespawnItem::setCapturable(bool value)
{
    info().isCapturable = value;
}
//------------------------------------------------------------------------------
void TRespawnItem::setMain(bool value)
{
    info().isMain = value;
}
//------------------------------------------------------------------------------
void TRespawnItem::setCaptureTime(quint32 time)
{
    info().captureTime = time;
}
//------------------------------------------------------------------------------
void TRespawnItem::setTeam(ETeam team)
{
    info().team = team;
}
//------------------------------------------------------------------------------
