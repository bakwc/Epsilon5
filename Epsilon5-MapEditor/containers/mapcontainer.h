// mapcontainer.h
#pragma once
#include "containers/container.h"
#include "containers/mapitem.h"
#include "containers/mapobjectcontainer.h"
#include "containers/maprespawncontainer.h"
//------------------------------------------------------------------------------
class TMapContainer : public QObject //TContainer<TMapContainer, TMapItem>
{
public:
    typedef quint32 TMapId;

public:
    TMapContainer(QObject* parent = 0);
//    void clear();
    TMapId addMap(const TMapInfo& info, const QIcon& preview);
    void removeMap(TMapId mapId);

    const TMapObjectContainer* objects(TMapId mapId) const;
    TMapObjectContainer* objects(TMapId mapId);

private:
};
//------------------------------------------------------------------------------
