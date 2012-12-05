// maprespawnscontainer.h
#pragma once
#include "stuctures.h"
#include "container.h"
//------------------------------------------------------------------------------
class TMapRespawnItem : public QObject
{
    Q_OBJECT
public:
    TMapRespawnItem();
    ~TMapRespawnItem();
    TMapRespawnItem(TMapRespawnInfo* mapInfo);

private:
    TMapRespawnInfo* mInfo;
};
//------------------------------------------------------------------------------
class TMapRespawnContainer : public TContainer
{
public:
    TMapRespawnContainer(QObject* parent = 0);
};
//------------------------------------------------------------------------------
