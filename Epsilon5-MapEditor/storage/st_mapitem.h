#pragma once
#include "storage/item_t.h"
#include "storage/st_storageinfos.h"
#include "storage/st_objectcontainer.h"
#include "storage/st_respawncontainer.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
class TMapItem : public TTItem<TMapInfo>
{
public:
    TMapItem();
    TMapItem(const TMapItem& map);
    TMapItem& operator=(const TMapItem& map);

    QString name() const;
    QSize size() const;
    quint32 width() const;
    quint32 height() const;

    void setName(const QString& name);
    void setSize(quint32 width, quint32 height);
    void setSize(const QSize& size);

private:
    TObjectContainer mObjects;
    TRespawnContainer mRespawns;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
