#include "st_sourceobjectitem.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
TSObjectItem::TSObjectItem(const TSObjectInfo& info)
    : TTItem(info)
{
}
//------------------------------------------------------------------------------
TSObjectItem::TSObjectItem(const TSObjectItem& object)
    : TTItem(object)
{
}
//------------------------------------------------------------------------------
TSObjectItem& TSObjectItem::operator =(const TSObjectItem& object)
{
    TTItem::operator =(object);
    return *this;
}
//------------------------------------------------------------------------------
quint32 TSObjectItem::objectId() const
{
    return info().id;
}
//------------------------------------------------------------------------------
quint32 TSObjectItem::width() const
{
    return info().width;
}
//------------------------------------------------------------------------------
quint32 TSObjectItem::height() const
{
    return info().height;
}
//------------------------------------------------------------------------------
QSize TSObjectItem::size() const
{
    return QSize(info().width, info().height);
}
//------------------------------------------------------------------------------
bool TSObjectItem::isDynamic() const
{
    return info().isDynamic;
}
//------------------------------------------------------------------------------
const QString& TSObjectItem::resourceName() const
{
    return info().name;
}
//------------------------------------------------------------------------------
void TSObjectItem::setObjectId(quint32 id)
{
    info().id = id;
}
//------------------------------------------------------------------------------
void TSObjectItem::setSize(const QSize& size)
{
    info().width = size.width();
    info().height = size.height();
}
//------------------------------------------------------------------------------
void TSObjectItem::setWidth(quint32 width)
{
    info().width = width;
}
//------------------------------------------------------------------------------
void TSObjectItem::setHeight(quint32 height)
{
    info().height = height;
}
//------------------------------------------------------------------------------
void TSObjectItem::setDynamic(bool value)
{
    info().isDynamic = value;
}
//------------------------------------------------------------------------------
void TSObjectItem::setResourceName(const QString& name)
{
    info().name = name.trimmed().replace("[ \t\n]", "_");
}
//------------------------------------------------------------------------------
bool TSObjectItem::validate()
{
    mValid = info().id > 0 && !info().name.isEmpty()
             && !info().name.contains("[ \t\n]");
    return mValid;
}
//------------------------------------------------------------------------------
QString TSObjectItem::pack() const
{
    QString str = QString("%1:%2:%3:%4:%5").arg(info().id).arg(info().width)
                  .arg(info().height).arg(info().isDynamic).arg(info().name);
    return str;
}
//------------------------------------------------------------------------------
bool TSObjectItem::unpack(const QString& string)
{
    const quint8 STRUCTURE_FIELDS_COUNT = 5;
    QStringList vars = string.split(":");
    bool isOk;
    if (vars.count() != STRUCTURE_FIELDS_COUNT) {
        return false;
    }
    info().id = vars[0].toUInt(&isOk);
    if (!isOk) {
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
    info().isDynamic = vars[3].toUInt(&isOk);
    if (!isOk) {
        return false;
    }
    info().name = vars[4].trimmed();
    return validate();
}
//------------------------------------------------------------------------------

