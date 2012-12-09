#pragma once
#include <QObject>
#include "container_t.h"
#include "st_objectitem.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
class TObjectContainer : public QObject, public TTContainer<TObjectItem>
{
    Q_OBJECT
public:
    typedef TObjectItem::TItemId TObjectItemId;

public:
    explicit TObjectContainer(QObject* parent = 0);
    TObjectContainer(const TObjectContainer& container);
    TObjectContainer& operator =(const TObjectContainer& containers);

    TObjectItemId addObject(const TObjectInfo& info);
    TObjectItemId addObject(const TObjectItem& object);
    void removeObject(const TObjectItem& object);
    void removeObject(TObjectItemId id);

    void loadObjectList(const QString& objectList,
            const QDir& baseDirectory = QDir::currentPath(),
            bool withResource = false);
    void saveObjectList(const QString& objectList,
            const QDir& baseDirectory = QDir::currentPath(),
            bool withResource = false) const;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
