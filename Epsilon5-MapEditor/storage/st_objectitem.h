#pragma once
#include "storage/item_t.h"
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
    QString name() const;

    void setObjectId(quint32 objectId);
    void setPos(const QPoint& pos);
    void setX(qint32 x);
    void setY(qint32 y);
    void setAngle(qreal angle);
    void setName(const QString& name);

    bool hasResource() const;
    bool validate();

    QString pack() const;
    bool unpack(const QString& string, bool withResourceName = false);
private:
    QString mName;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
