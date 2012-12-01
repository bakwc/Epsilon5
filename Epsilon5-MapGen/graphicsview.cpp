#include "graphicsview.h"
#include "mapitem.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QScrollBar>


GraphicsView::GraphicsView(QGraphicsScene *scene, QList<utils::Object> &objsList,
                           QList<QPixmap> &objPix, QWidget *parent) :
    QGraphicsView(scene, parent), _objsLst(objsList), _objPix(objPix)
{
    //    setMouseTracking(true);
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsItem *item = new MapItem(_objsLst.at(_itemId), _objPix.at(_itemId));

    QScrollBar *hs = horizontalScrollBar();
    QScrollBar *vs = verticalScrollBar();

    QPoint vPoint = QPoint(event->x() + hs->value() - _objsLst.at(_itemId).width/2,
                           event->y() + vs->value() - _objsLst.at(_itemId).height/2);

    item->setPos(vPoint);
    scene()->addItem(item);
    update();
}

void GraphicsView::selectedItem(int item)
{
    _itemId = item;
    qDebug() << _objsLst.at(_itemId).name;
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
