#pragma once
#include <QObject>
#include "storage/st_container_t.h"
#include "storage/st_sourceobjectitem.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
class TSObjectContainer
    : public QObject
    , public TTContainer<TSObjectItem, TSObjectInfo>
{
    Q_OBJECT
public:
    typedef TSObjectItem::TItemId TSObjectItemId;

public:
    explicit TSObjectContainer(QObject* parent = 0);
    TSObjectContainer(const TSObjectContainer& container);
    TSObjectContainer& operator =(const TSObjectContainer& container);

    void loadObjectList(const QString& objectList,
            const QDir& baseDirectory = QDir::currentPath());
    void saveObjectList(const QString& objectList) const;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
