#pragma once
#include <QStandardItemModel>
#include "storage/st_item_t.h"
#include "storage/st_mapcontainer.h"
#include "storage/st_sourceobjectcontainer.h"
//------------------------------------------------------------------------------
template<typename T, typename Titem, typename Tinfo>
class TTItemModelHelper
{
    typedef typename Titem::TItemId TItemId;
public:
    static void addItemToModel(const Titem& item, QStandardItemModel* model,
            const QIcon& icon = QIcon()) {
        QStandardItem* viewItem = new QStandardItem;
        viewItem->setText(item.pack());
        viewItem->setData(item.itemId());
        viewItem->setEditable(false);
        viewItem->setIcon(icon);
        model->appendRow(viewItem);
    }

    // Get item from model of T container
    static const Titem* itemFromModelIndex(const T& container,
            const QStandardItemModel* model, const QModelIndex& index) {
        QStandardItem* viewItem = model->itemFromIndex(index);
        if (!viewItem) {
            return 0;
        }
        return &container.item(viewItem->data().toUInt());
    }

    // Get itemId from model of T container
    static TItemId itemIdFromModelIndex(const T& container,
            const QStandardItemModel* model, const QModelIndex& index) {
        QStandardItem* viewItem = model->itemFromIndex(index);
        if (!viewItem) {
            return 0;
        }
        return container[viewItem->data().toUInt()].itemId();
    }
};
//------------------------------------------------------------------------------
typedef TTItemModelHelper<containers::TMapContainer,
        containers::TMapItem, containers::TMapInfo> TMapHelper;
typedef TTItemModelHelper<containers::TObjectContainer,
        containers::TObjectItem, containers::TObjectInfo> TObjectHelper;
typedef TTItemModelHelper<containers::TRespawnContainer,
        containers::TRespawnItem, containers::TRespawnInfo> TRespawnHelper;
typedef TTItemModelHelper<containers::TSObjectContainer,
        containers::TSObjectItem, containers::TSObjectInfo> TSObjectHelper;
//------------------------------------------------------------------------------
