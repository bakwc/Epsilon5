#pragma once
#include "storage/item_t.h"
#include "storage/st_storageinfos.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
class TRespawnItem : public TTItem<TRespawnInfo>
{
public:
    TRespawnItem();
    TRespawnItem(const TRespawnItem& respawn);
    TRespawnItem& operator=(const TRespawnItem& respawn);

    quint32 x() const;
    quint32 y() const;
    QPoint pos() const;
    quint32 captureRadius() const;
    quint32 spawnRadius() const;
    bool isCapturable() const;
    bool isMain() const;
    quint32 captureTime() const;
    ETeam team() const;

    void setX(quint32 x);
    void setY(quint32 y);
    void setPos(const QPoint& pos);
    void setCaptureRadius(quint32 radius);
    void setSpawnRadius(quint32 radius);
    void setCapturable(bool value = true);
    void setMain(bool value = true);
    void setCaptureTime(quint32 time);
    void setTeam(ETeam team);
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
