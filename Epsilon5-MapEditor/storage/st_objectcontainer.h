#pragma once
#include <QObject>
#include "st_container_t.h"
#include "st_objectitem.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
class TObjectContainer
    : public QObject
    , public TTContainer<TObjectItem, TObjectInfo>
{
    Q_OBJECT
public:
    typedef TObjectItem::TItemId TObjectItemId;

public:
    explicit TObjectContainer(QObject* parent = 0);
    TObjectContainer(const TObjectContainer& container);
    TObjectContainer& operator =(const TObjectContainer& containers);

    void loadObjectList(const QString& objectList);
    void saveObjectList(const QString& objectList) const;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
