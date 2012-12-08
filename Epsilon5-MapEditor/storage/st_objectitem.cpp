#include "storage/st_objectitem.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
TObjectItem::TObjectItem(const TObjectInfo& info)
    : TTItem(info)
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
quint32 TObjectItem::objectId() const
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
void TObjectItem::setObjectId(quint32 id)
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
bool TObjectItem::validate()
{
    mValid = info().id > 0;
    return mValid;
}
//------------------------------------------------------------------------------
QString TObjectItem::pack() const
{
    return QString("%1:%2:%3:%4").arg(info().x).arg(info().y)
            .arg(info().angle).arg(info().id);
}
//------------------------------------------------------------------------------
bool TObjectItem::unpack(const QString& string)
{
    const quint8 STRUCTURE_FIELDS_COUNT = 4;
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
    info().angle = vars[2].toDouble(&isOk);
    if (!isOk) {
        return false;
    }
    info().id = vars[3].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------
