#pragma once
#include <QObject>
#include "storage/st_container_t.h"
#include "storage/st_respawnitem.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
class TRespawnContainer : public QObject, public TTContainer<TRespawnItem, TRespawnInfo>
{
    Q_OBJECT
public:
    typedef TRespawnItem::TItemId TRespawnItemId;

public:
    explicit TRespawnContainer(QObject* parent = 0);
    TRespawnContainer(const TRespawnContainer& container);
    TRespawnContainer& operator =(const TRespawnContainer& container);

    void loadRespawnList(const QString& respawnList);
    void saveRespawnList(const QString& respawnList) const;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
