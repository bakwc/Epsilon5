#pragma once
#include <QStandardItemModel>
#include "storage/st_mapcontainer.h"
//------------------------------------------------------------------------------
template<typename T, typename Titem>
class TTItemModelHelper
{
public:
    static void addItemToModel(const Titem& item, QStandardItemModel* model) {
        QStandardItem* viewItem = new QStandardItem;
        viewItem->setText(item.pack());
        viewItem->setData(item.itemId());
        model->appendRow(viewItem);
    }

    static const Titem& itemFromModel(const T& container,
            const QModelIndex& index) {
        return container.item(index.data().toUInt());
    }


};
//------------------------------------------------------------------------------
