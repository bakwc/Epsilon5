#include "container.h"
//------------------------------------------------------------------------------
TContainer::TContainer(QObject* parent)
    : QObject(parent)
    , mModel(new QStandardItemModel(this))
    , mLastValidId(0)
{
}
//------------------------------------------------------------------------------
