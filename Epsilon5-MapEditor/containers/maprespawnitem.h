// maprespawnitem.h
#pragma once
#include <QObject>
#include "containers/structures.h"
//------------------------------------------------------------------------------
class TMapRespawnItem : public QObject
{
    Q_OBJECT
public:
    TMapRespawnItem(QObject* parent = 0);
    TMapRespawnItem(const TMapRespawnItem& respawn);
    TMapRespawnItem(const TMapRespawnInfo& respawnInfo,
        QObject* parent = 0);
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
