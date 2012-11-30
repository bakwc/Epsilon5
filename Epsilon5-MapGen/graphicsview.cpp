#include "graphicsview.h"
#include "mapitem.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>


GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) :
    QGraphicsView(scene, parent)
{
//    setMouseTracking(true);
}

void GraphicsView::setItem(const QString &str, const QSizeF &s, const QPixmap &pix)
{
    _itemName = str;
    _itemSize = s;
    _itemPix  = pix;
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsItem *item = new MapItem(_itemSize, _itemPix);
    item->setPos(event->pos());
    scene()->addItem(item);
    update();
}

//void GraphicsView::mouseMoveEvent(QMouseEvent *event)
//{
//    _itemPrevPoint = event->pos();
//    update();
//}

//void GraphicsView::paintEvent(QPaintEvent *event)
//{
//    QPainter p;
//    p.begin(this);

////    p.setBrush(QBrush(Qt::green, Qt::Dense1Pattern));
//    p.setPen(QPen(QBrush(Qt::green, Qt::Dense1Pattern), 3, Qt::DashLine));
//    p.drawRect(_itemPrevPoint.x() - _itemSize.width()/2,  _itemPrevPoint.y() - _itemSize.height()/2,
//               _itemSize.width(), _itemSize.height());

//    p.end();
//}
