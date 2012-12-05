// graphicsview.cpp
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QScrollBar>
#include "graphicsview.h"
#include "mapitem.h"
//------------------------------------------------------------------------------
TGraphicsView::TGraphicsView(QGraphicsScene* scene, TObjectsList& objectsList,
        TPixmapsList& pixmapList, QWidget* parent)
    : QGraphicsView(scene, parent)
    , mObjectsList(objectsList)
    , mPixmapsList(pixmapList)
    , mItemId(0)
{
//    setMouseTracking(true);
    connect(&mItemSignal, SIGNAL(mapItemSignal(QString, QPointF, qreal)),
            SLOT(itemSlot(QString, QPointF, qreal)));
}
//------------------------------------------------------------------------------
void TGraphicsView::addMapItem(const utils::TMapLine& ml)
{
    TMapItem* item = new TMapItem(mObjectsList.at(ml.id - 1),
            mPixmapsList.at(ml.id - 1));
    item->setPos(ml.x, ml.y);
    item->setRotation(ml.angle);
    scene()->addItem(item);
}
//------------------------------------------------------------------------------
void TGraphicsView::mouseDoubleClickEvent(QMouseEvent* event)
{
    QGraphicsItem* item = new TMapItem(mObjectsList.at(mItemId),
            mPixmapsList.at(mItemId));
    QScrollBar* hs = horizontalScrollBar();
    QScrollBar* vs = verticalScrollBar();
    QPoint vPoint = QPoint(
            event->x() + hs->value() - mObjectsList.at(mItemId).width / 2,
            event->y() + vs->value() - mObjectsList.at(mItemId).height / 2);
    item->setPos(vPoint);
    scene()->addItem(item);
    update();
}
//------------------------------------------------------------------------------
void TGraphicsView::selectedItem(int item)
{
    mItemId = item;
    qDebug() << mObjectsList.at(mItemId).name;
}
//------------------------------------------------------------------------------
void TGraphicsView::itemSlot(QString name, QPointF itemPos, qreal itemRot)
{
    qDebug() << name << " pos: " << itemPos << " roration: " << itemRot;
}
//------------------------------------------------------------------------------
//void GraphicsView::mouseMoveEvent(QMouseEvent* event)
//{
//    _itemPrevPoint = event->pos();
//    update();
//}
//------------------------------------------------------------------------------
//void GraphicsView::paintEvent(QPaintEvent* event)
//{
//    QPainter p;
//    p.begin(this);
//------------------------------------------------------------------------------
////    p.setBrush(QBrush(Qt::green, Qt::Dense1Pattern));
//    p.setPen(QPen(QBrush(Qt::green, Qt::Dense1Pattern), 3, Qt::DashLine));
//    p.drawRect(_itemPrevPoint.x() - _itemSize.width()/2,
//               _itemPrevPoint.y() - _itemSize.height()/2,
//               _itemSize.width(), _itemSize.height());
//    p.end();
//}
//------------------------------------------------------------------------------
