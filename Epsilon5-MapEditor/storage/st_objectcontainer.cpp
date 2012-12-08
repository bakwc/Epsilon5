#include "storage/st_objectcontainer.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
TObjectContainer::TObjectContainer(QObject* parent)
    : QObject(parent)
    , TTContainer()
{
}
//------------------------------------------------------------------------------
TObjectContainer::TObjectContainer(const TObjectContainer& container)
    : QObject(container.parent())
    , TTContainer(container)
{
}
//------------------------------------------------------------------------------
TObjectContainer& TObjectContainer::operator =(const TObjectContainer& container)
{
    TTContainer::operator =(container);
    return *this;
}
//------------------------------------------------------------------------------
