#include "containers/mapcontainer.h"
//------------------------------------------------------------------------------
TMapContainer::TMapContainer(QObject* parent)
//    : TContainer(parent)
    : QObject(parent)
{
}
//------------------------------------------------------------------------------
//void TMapContainer::clear()
//{
//    mModel->clear();
//}
//------------------------------------------------------------------------------
TMapContainer::TMapId TMapContainer::addMap(const TMapInfo& info, const QIcon& preview)
{
    Q_UNUSED(info);
    Q_UNUSED(preview);
    return 0;
}
//------------------------------------------------------------------------------
void TMapContainer::removeMap(TMapContainer::TMapId mapId)
{
    Q_UNUSED(mapId);
}
//------------------------------------------------------------------------------
