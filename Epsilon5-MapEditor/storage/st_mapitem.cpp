#include "storage/st_mapitem.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
TMapItem::TMapItem(const TMapInfo& info,
        const TObjectContainer& objects, const TRespawnContainer& respawns)
    : TTItem(info)
    , mObjects(objects)
    , mRespawns(respawns)
    , mBackgroundFile()
{
}
//------------------------------------------------------------------------------
TMapItem::TMapItem(const TMapItem& map)
    : TTItem(map)
    , mObjects(map.mObjects)
    , mRespawns(map.mRespawns)
    , mBackgroundFile(map.mBackgroundFile)
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
bool TMapItem::validate()
{
    mValid = !(info().name).isEmpty();
    return mValid;
}
//------------------------------------------------------------------------------
const TObjectContainer& TMapItem::objects() const
{
    return mObjects;
}
//------------------------------------------------------------------------------
TObjectContainer& TMapItem::objects()
{
    return mObjects;
}
//------------------------------------------------------------------------------
const TRespawnContainer& TMapItem::respawns() const
{
    return mRespawns;
}
//------------------------------------------------------------------------------
TRespawnContainer& TMapItem::respawns()
{
    return mRespawns;
}
//------------------------------------------------------------------------------
QString TMapItem::pack() const
{
    return QString("%1:%2x%3").arg(info().name)
            .arg(info().width).arg(info().height);
}
//------------------------------------------------------------------------------
bool TMapItem::unpack(const QString& string)
{
    const quint8 STRUCTURE_FIELDS_COUNT = 4;
    QStringList vars = string.split(":");
    bool isOk;
    if (vars.count() != STRUCTURE_FIELDS_COUNT) {
        return false;
    }
    info().name = vars[0].trimmed();
    if (info().name.isEmpty()) {
        return false;
    }
    info().width = vars[1].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    info().height = vars[2].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------
const QString& TMapItem::background() const
{
    return mBackgroundFile;
}
//------------------------------------------------------------------------------
void TMapItem::setBackground(const QString &file)
{
    mBackgroundFile = file.trimmed();
}
//------------------------------------------------------------------------------
