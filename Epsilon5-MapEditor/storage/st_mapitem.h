#pragma once
#include "storage/st_item_t.h"
#include "storage/st_storageinfo.h"
#include "storage/st_objectcontainer.h"
#include "storage/st_respawncontainer.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
class TMapItem : public TTItem<TMapInfo>
{
public:
    TMapItem(const TMapInfo& info = TMapInfo(),
             const TObjectContainer& objects = TObjectContainer(),
             const TRespawnContainer& respawns = TRespawnContainer());
    TMapItem(const TMapItem& map);
    TMapItem& operator=(const TMapItem& map);

    QString name() const;
    QSize size() const;
    quint32 width() const;
    quint32 height() const;
    QColor color() const;

    void setName(const QString& name);
    void setSize(quint32 width, quint32 height);
    void setSize(const QSize& size);
    void setColor(const QColor& color);

    bool validate();

    const TObjectContainer& objects() const;
    TObjectContainer& objects();
    const TRespawnContainer& respawns() const;
    TRespawnContainer& respawns();
    const QString& background() const;
    void setBackground(const QString& file);

    QString pack() const;
    bool unpack(const QString& string);

private:
    TObjectContainer mObjects;
    TRespawnContainer mRespawns;
    QString mBackgroundFile;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
