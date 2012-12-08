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
    explicit TRespawnContainer(QObject* parent = 0);
    TRespawnContainer(const TRespawnContainer& container);
    TRespawnContainer& operator =(const TRespawnContainer& container);
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
