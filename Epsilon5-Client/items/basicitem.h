#ifndef BASICITEM_H
#define BASICITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QImage>

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

    void SetPix(const QImage& pix);

    EItemType ItemType() const { return Type; }
    const QSizeF& GetSize() const { return Size; }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    EItemType   Type;
    QSizeF      Size;
    QImage     Pix;
};

}

#endif // BASICITEM_H
