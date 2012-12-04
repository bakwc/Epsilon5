#include "scene.h"
#include "items/tbulletitem.h"
#include "items/tobjectitem.h"
#include "items/tplayeritem.h"
#include "../utils/uexception.h"

TScene::TScene(QObject *parent) :
    QGraphicsScene(parent)
{
    for (int i=0; i < basic::BasicItem::EItemType_MAX_VALUE; ++i) {
        ItemsTypeTable.insert((basic::BasicItem::EItemType)i, DItemsTable());
    }
}

basic::BasicItem *TScene::AddItem(basic::BasicItem *item, int itemId)
{
    DItemsTable& table = *ItemsTypeTable.find(item->ItemType());
    table.insert(itemId, item);
    this->addItem(item);
    return item;
}

bool TScene::IsContains(basic::BasicItem::EItemType type, int itemId)
{
    const DItemsTable& table = ItemsTypeTable.value(type);
    return table.contains(itemId);
}

basic::BasicItem *TScene::GetItem(basic::BasicItem::EItemType type, int itemId)
{
    DItemsTable& table = *ItemsTypeTable.find(type);
    DItemsTable::Iterator it = table.find(itemId);
    if (it != table.end())
        return *it;

//    throw UException(Q_FUNC_INFO + "error");
    return NULL;
}

void TScene::ClearItems(basic::BasicItem::EItemType type)
{
    DItemsTable& table = *ItemsTypeTable.find(type);
    DItemsTable::Iterator it = table.begin();
    while(it != table.end()) {
        basic::BasicItem *item = it.value();
        this->removeItem(item);
        delete item;
        table.erase(it++);
    }
}
