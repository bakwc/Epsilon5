// container.cpp
#include "containers/container.h"
//------------------------------------------------------------------------------
template<typename Tmodel, typename Titem>
TContainer<Tmodel, Titem>::TContainer(QObject* parent)
    : QObject(parent)
//    : QStandardItemModel(parent)
    , mModel(new Tmodel(this))
    , mLastValidId(0)
{
}
//------------------------------------------------------------------------------
template<typename Tmodel, typename Titem>
Titem* TContainer<Tmodel, Titem>::item(int row, int column) const
{
    return qobject_cast<Titem>(QStandardItemModel::item(row, column));
}
//------------------------------------------------------------------------------
template<typename Tmodel, typename Titem>
QAbstractItemModel* TContainer<Tmodel, Titem>::model() const
{
    return this;
}
//------------------------------------------------------------------------------
