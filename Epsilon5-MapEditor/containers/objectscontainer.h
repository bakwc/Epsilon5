#pragma once
#include "object.h"
#include "container.h"
//------------------------------------------------------------------------------
class TMapObjectItem : public QObject
{
    Q_OBJECT
public:
    TMapObjectItem();
    ~TMapObjectItem();
    TMapObjectItem(TMapObjectInfo* mapInfo);

private:
    TMapObjectInfo* mInfo;
};
//------------------------------------------------------------------------------
class TMapObjectContainer : public TContainer
{
public:
    TMapObjectContainer(QObject* parent = 0);
    TMapObjectContainer(TMapObjectContainer* container, QObject* parent = 0);
};
//------------------------------------------------------------------------------
