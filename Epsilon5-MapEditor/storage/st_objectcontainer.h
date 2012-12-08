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
    explicit TObjectContainer(QObject* parent = 0);
    TObjectContainer(const TObjectContainer& container);
    TObjectContainer& operator =(const TObjectContainer& containers);
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
