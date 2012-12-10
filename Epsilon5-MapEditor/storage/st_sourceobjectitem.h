#pragma once
#include "st_storageinfo.h"
#include "st_item_t.h"
//------------------------------------------------------------------------------
namespace containers {
//------------------------------------------------------------------------------
class TSObjectItem : public TTItem<TSObjectInfo>
{
public:
    TSObjectItem(const TSObjectInfo& info = TSObjectInfo());
    TSObjectItem(const TSObjectItem& object);
    TSObjectItem& operator=(const TSObjectItem& object);

    quint32 objectId() const;
    quint32 width() const;
    quint32 height() const;
    QSize size() const;
    bool isDynamic() const;
    const QString& resourceName() const;

    void setObjectId(quint32 objectId);
    void setSize(const QSize& size);
    void setWidth(quint32 width);
    void setHeight(quint32 height);
    void setDynamic(bool value = true);
    void setResourceName(const QString& name);

    bool validate();

    QString pack() const;
    bool unpack(const QString& string);
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
