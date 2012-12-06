#include "containers/mapcontainer.h"
//------------------------------------------------------------------------------
TMapContainer::TMapContainer(QObject* parent)
    : TContainer(parent)
{
}
//------------------------------------------------------------------------------
TMapContainer::TMapContainer(const TMapContainer &container)
    : TContainer(container.parent())
{
}
//------------------------------------------------------------------------------
TMapContainer::~TMapContainer()
{
}
//------------------------------------------------------------------------------
void TMapContainer::addMap(const TMapInfo &info)
{
    Q_UNUSED(info);
}
//------------------------------------------------------------------------------
void TMapContainer::removeMap(const QModelIndex &index)
{
    Q_UNUSED(index);
}
//------------------------------------------------------------------------------
void TMapContainer::loadFromFile(const QString &fileName)
{
    Q_UNUSED(fileName);
}
//------------------------------------------------------------------------------
void TMapContainer::saveToFile(const QString &fileName)
{
    Q_UNUSED(fileName);
}
//------------------------------------------------------------------------------
