// maprespawnitem.h
#pragma once
#include <QStandardItem>
#include "containers/structures.h"
//------------------------------------------------------------------------------
class TMapRespawnItem : public QObject
{
    Q_OBJECT
public:
//    TMapRespawnItem();
    TMapRespawnItem(QObject* parent = 0);
    TMapRespawnItem(const TMapRespawnItem& mapInfo, QObject* parent = 0)
        : mInfo(mapInfo.mInfo)
        , mValid(mapInfo.mValid)
    {}

//    TMapRespawnItem(const TMapRespawnInfo& mapInfo, QObject* parent = 0);
    TMapRespawnItem(const TMapRespawnInfo& mapInfo);
    ~TMapRespawnItem();
    TMapRespawnInfo respawnInfo() const;
    QString serialize();
    bool isValid();

private:
    bool checkData();

private:
    TMapRespawnInfo* mInfo;
    bool mValid;
};
//------------------------------------------------------------------------------
Q_DECLARE_METATYPE(TMapRespawnItem)
//------------------------------------------------------------------------------
