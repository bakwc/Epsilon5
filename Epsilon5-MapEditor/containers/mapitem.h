// mapitem.h
#pragma once
#include <QStandardItem>
#include "containers/structures.h"
#include "containers/mapobjectcontainer.h"
#include "containers/maprespawncontainer.h"
//------------------------------------------------------------------------------
class TMapItem : public QStandardItem
{
public:
    TMapItem();

private:
    TMapInfo* mInfo;
    TMapObjectContainer* mObjects;
    TMapRespawnContainer* mRespawns;
};
//------------------------------------------------------------------------------
