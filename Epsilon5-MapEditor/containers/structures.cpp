// structures.cpp
// TODO: Refactor this code. Make util functions for pack/unpack
// or move'em ouside (i.e. in TMap*Item classes)

#include <QStringList>
#include "containers/structures.h"
//------------------------------------------------------------------------------
const quint32 DEFAULT_MAP_WIDTH = 4000;
const quint32 DEFAULT_MAP_HEIGTH = DEFAULT_MAP_WIDTH;
//------------------------------------------------------------------------------
TMapInfo::TMapInfo()
    : name(QString(QObject::tr("Unnamed map")))
    , width(DEFAULT_MAP_WIDTH)
    , height(DEFAULT_MAP_HEIGTH)
{
}
//------------------------------------------------------------------------------
TMapInfo::TMapInfo(const TMapInfo &info)
    : name(info.name)
    , width(info.width)
    , height(info.height)
{
}
//------------------------------------------------------------------------------
QString TMapInfo::pack()
{
    return QString("%1:%2x%3").arg(name).arg(width).arg(height);
}
//------------------------------------------------------------------------------
bool TMapInfo::unpack(const QString& string)
{
    const quint8 STRUCTURE_FIELDS_COUNT = 4;
    QStringList vars = string.split(":");
    bool isOk;
    if (vars.count() != STRUCTURE_FIELDS_COUNT) {
        return false;
    }
    name = vars[0].trimmed();
    if (name.isEmpty()) {
        return false;
    }
    width = vars[1].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    height = vars[2].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------
TMapObjectInfo::TMapObjectInfo()
    : id(0)
    , x(0)
    , y(0)
    , angle(0.0)
{
}
//------------------------------------------------------------------------------
TMapObjectInfo::TMapObjectInfo(const TMapObjectInfo &info)
    : id(info.id)
    , x(info.x)
    , y(info.y)
    , angle(info.angle)
{
}
//------------------------------------------------------------------------------
QString TMapObjectInfo::pack()
{
    return QString("%1:%2:%3:%4").arg(x).arg(y).arg(angle).arg(id);
}
//------------------------------------------------------------------------------
bool TMapObjectInfo::unpack(const QString& string)
{
    const quint8 STRUCTURE_FIELDS_COUNT = 4;
    QStringList vars = string.split(":");
    bool isOk;
    if (vars.count() != STRUCTURE_FIELDS_COUNT) {
        return false;
    }
    x = vars[0].toInt(&isOk);
    if (!isOk) {
        return false;
    }
    y = vars[1].toInt(&isOk);
    if (!isOk) {
        return false;
    }
    angle = vars[2].toDouble(&isOk);
    if (!isOk) {
        return false;
    }
    id = vars[3].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------
TMapRespawnInfo::TMapRespawnInfo()
    : x(0)
    , y(0)
    , captureRadius(10)
    , spawnRadius(200)
    , isCapturable(false)
    , isMain(false)
    , captureTime(10)
    , team(T_Neutral)
{
}
//------------------------------------------------------------------------------
TMapRespawnInfo::TMapRespawnInfo(const TMapRespawnInfo &info)
    : x(info.x)
    , y(info.y)
    , captureRadius(info.captureRadius)
    , spawnRadius(info.spawnRadius)
    , isCapturable(info.isCapturable)
    , isMain(info.isMain)
    , captureTime(info.captureTime)
    , team(info.team)
{
}
//------------------------------------------------------------------------------
QString TMapRespawnInfo::pack()
{
    return QString("%1:%2:%3:%4:%5:%6:%7:%8").arg(x).arg(y).arg(captureRadius)
           .arg(spawnRadius).arg(isCapturable)
           .arg(isMain).arg(captureTime).arg(team);
}
//------------------------------------------------------------------------------
bool TMapRespawnInfo::unpack(const QString& string)
{
    const quint8 STRUCTURE_FIELDS_COUNT = 8;
    QStringList vars = string.split(":");
    bool isOk;
    if (vars.count() != STRUCTURE_FIELDS_COUNT) {
        return false;
    }
    x = vars[0].toInt(&isOk);
    if (!isOk) {
        return false;
    }
    y = vars[1].toInt(&isOk);
    if (!isOk) {
        return false;
    }
    captureRadius = vars[2].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    spawnRadius = vars[3].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    isCapturable = (bool) vars[4].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    isMain = (bool) vars[5].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    captureTime = vars[6].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    team = (ETeam)(vars[7].toUInt(&isOk) % ETEAM_SIZE);
    if (!isOk) {
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------
