#pragma once
#include "storage/item_t.h"
#include "storage/st_storageinfos.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
class TObjectItem : public TTItem<TObjectInfo>
{
public:
    TObjectItem();
    TObjectItem(const TObjectItem& object);
    TObjectItem& operator=(const TObjectItem& object);

    quint32 id() const;
    qint32 x() const;
    qint32 y() const;
    QPoint pos() const;
    qreal angle() const;

    void setId(quint32 id);
    void setPos(const QPoint& pos);
    void setX(qint32 x);
    void setY(qint32 y);
    void setAngle(qreal angle);
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
