// mapobjectitem.h
#pragma once
#include <QStandardItem>
#include "containers/structures.h"
//------------------------------------------------------------------------------
class TMapObjectItem : public QStandardItem
{
public:
    TMapObjectItem();
    ~TMapObjectItem();
    TMapObjectItem(TMapObjectInfo* mapInfo);

private:
    TMapObjectInfo* mInfo;
};
//------------------------------------------------------------------------------
