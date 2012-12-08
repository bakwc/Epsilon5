#pragma once
#include <QObject>
#include "storage/container_t.h"
#include "storage/st_respawnitem.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
class TRespawnContainer : public QObject, public TTContainer<TRespawnItem>
{
    Q_OBJECT
public:
    typedef TRespawnItem::TItemId TRespawnItemId;

public:
    explicit TRespawnContainer(QObject* parent = 0);
    TRespawnContainer(const TRespawnContainer& container);
    TRespawnContainer& operator =(const TRespawnContainer& container);

    TRespawnItemId addRespawn(const TRespawnInfo& info);
    TRespawnItemId addRespawn(const TRespawnItem& item);
    void removeRespawn(const TRespawnItem& item);
    void removeRespawn(TRespawnItemId id);

    void loadRespawnList(const QString& respawnList,
            const QDir& baseDirectory = QDir::currentPath());
    void saveRespawnList(const QString& respawnList,
            const QDir& baseDirectory = QDir::currentPath()) const;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
