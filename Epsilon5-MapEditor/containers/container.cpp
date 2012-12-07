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
TContainer::TContainer(const TContainer& container)
    : QObject(container.parent())
    , mModel(new QStandardItemModel(this))
    , mLastValidId(container.mLastValidId)
{
    for (int i = 0; i < container.mModel->rowCount(); ++i) {
        QStandardItem* item = container.mModel->item(i);
        mModel->appendRow(item->clone());
    }
}
//------------------------------------------------------------------------------
TContainer::~TContainer()
{
}
//------------------------------------------------------------------------------
TContainer& TContainer::operator =(const TContainer& container)
{
    mModel = new QStandardItemModel(container.mModel);
    mLastValidId = container.mLastValidId;
    return *this;
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
    return mModel->rowCount();
}
//------------------------------------------------------------------------------
