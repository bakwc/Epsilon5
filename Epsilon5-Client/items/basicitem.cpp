#include "basicitem.h"
#include <QPainter>
#include <QBrush>

namespace basic {

QRectF BasicItem::boundingRect() const
{
    return QRectF(QPointF(0, 0), Size);
}

BasicItem::BasicItem(EItemType type, const QSizeF &size) :
    Type(type), Size(size)
{
}

}
