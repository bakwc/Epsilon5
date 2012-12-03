#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QHash>
#include "items/basicitem.h"

class TBulletItem;
class TPlayerItem;
class TObjectItem;

class TScene : public QGraphicsScene
{
    Q_OBJECT

    typedef QHash<qint32, basic::BasicItem*> DItemsTable;
    typedef QHash< basic::BasicItem::EItemType, DItemsTable > DItemsTypeTable;

public:
    explicit TScene(QObject *parent = 0);

    basic::BasicItem* AddItem(basic::BasicItem* item, int itemId);
    bool IsContains(basic::BasicItem::EItemType type, int itemId);
    basic::BasicItem* GetItem(basic::BasicItem::EItemType type, int itemId);

    void ClearItems(basic::BasicItem::EItemType type);
    
signals:
    
public slots:

private:
    DItemsTypeTable ItemsTypeTable;
};

#endif // SCENE_H
