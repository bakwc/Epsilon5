#pragma once
#include <QObject>
#include "storage/container_t.h"
#include "storage/st_storageinfos.h"
#include "storage/st_mapitem.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
class TMapContainer : public QObject, public TTContainer<TMapItem>
{
    Q_OBJECT
public:
    explicit TMapContainer(QObject* parent = 0);
    quint32 addMap(const TMapItem& mapItem);
    void removeMap(const TMapItem& mapItem);

private:
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
