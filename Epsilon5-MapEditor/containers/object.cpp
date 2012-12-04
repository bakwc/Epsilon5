#include "object.h"

TObjectContainer::TObjectContainer(QObject *parent) :
    QObject(parent)
{
}

int TObjectContainer::count()
{
    return mItems.count();
}

TObject TObjectContainer::operator [](int value)
{
    return mItems.value(value);
}
