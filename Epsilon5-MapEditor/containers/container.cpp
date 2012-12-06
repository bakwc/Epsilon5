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
void TContainer::clear()
{
    mModel->clear();
    mLastValidId = 0;
}
//------------------------------------------------------------------------------
int TContainer::count() const
{
    mModel->rowCount();
}
//------------------------------------------------------------------------------
