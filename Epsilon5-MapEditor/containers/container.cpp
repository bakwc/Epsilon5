// container.cpp
#include "containers/container.h"
//------------------------------------------------------------------------------
TContainer::TContainer(QObject* parent)
    : QObject(parent)
    , mModel(new QStandardItemModel(this))
    , mLastValidId(0)
{
}
//------------------------------------------------------------------------------
QStandardItemModel* TContainer::model() const
{
    return mModel;
}
//------------------------------------------------------------------------------
