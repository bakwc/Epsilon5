#include "storage/st_respawnitem.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
TRespawnItem::TRespawnItem(const TRespawnInfo& info)
    : TTItem(info)
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
    info().y = pos.y();
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
bool TRespawnItem::validate()
{
    mValid = true;
    return mValid;
}
//------------------------------------------------------------------------------
QString TRespawnItem::pack() const
{
    return QString("%1:%2:%3:%4:%5:%6:%7:%8").arg(info().x).arg(info().y)
           .arg(info().captureRadius)
           .arg(info().spawnRadius).arg(info().isCapturable)
           .arg(info().isMain).arg(info().captureTime).arg(info().team);
}
//------------------------------------------------------------------------------
bool TRespawnItem::unpack(const QString& string)
{
    const quint8 STRUCTURE_FIELDS_COUNT = 8;
    QStringList vars = string.split(":");
    bool isOk;
    if (vars.count() != STRUCTURE_FIELDS_COUNT) {
        return false;
    }
    info().x = vars[0].toInt(&isOk);
    if (!isOk) {
        return false;
    }
    info().y = vars[1].toInt(&isOk);
    if (!isOk) {
        return false;
    }
    info().captureRadius = vars[2].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    info().spawnRadius = vars[3].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    info().isCapturable = (bool) vars[4].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    info().isMain = (bool) vars[5].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    info().captureTime = vars[6].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    info().team = (ETeam)(vars[7].toUInt(&isOk) % ETEAM_SIZE);
    if (!isOk) {
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------
