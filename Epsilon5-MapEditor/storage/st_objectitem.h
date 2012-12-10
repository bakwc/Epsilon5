#pragma once
#include "storage/st_item_t.h"
#include "storage/st_storageinfo.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
class TObjectItem : public TTItem<TObjectInfo>
{
public:
    TObjectItem(const TObjectInfo& info = TObjectInfo());
    TObjectItem(const TObjectItem& object);
    TObjectItem& operator=(const TObjectItem& object);

    quint32 objectId() const;
    qint32 x() const;
    qint32 y() const;
    QPoint pos() const;
    qreal angle() const;

    void setObjectId(quint32 objectId);
    void setPos(const QPoint& pos);
    void setX(qint32 x);
    void setY(qint32 y);
    void setAngle(qreal angle);

    bool validate();

    QString pack() const;
    bool unpack(const QString& string);
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
