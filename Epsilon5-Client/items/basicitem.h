#ifndef BASICITEM_H
#define BASICITEM_H

#include <QGraphicsItem>

namespace basic {

class BasicItem : public QGraphicsItem
{
public:

    enum EItemType {
        BULLET,
        OBJECT,
        PLAYER,
        EItemType_MAX_VALUE
    };

    BasicItem(EItemType type, const QSizeF& size);

    QRectF boundingRect() const;

    EItemType ItemType() const { return Type; }
    const QSizeF& GetSize() const { return Size; }

private:
    EItemType   Type;
    QSizeF      Size;
};

}

#endif // BASICITEM_H
