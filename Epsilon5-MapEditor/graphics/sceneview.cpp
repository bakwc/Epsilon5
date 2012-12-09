#include <QPaintEvent>
#include <QGraphicsSceneMouseEvent>
#include "sceneview.h"
//------------------------------------------------------------------------------
TSceneView::TSceneView(TScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
    , mFixedPoint(QPoint())
    , mPx(new QPixmap())
{
}
//------------------------------------------------------------------------------
void TSceneView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
}
//------------------------------------------------------------------------------
void TSceneView::setBackground(const QPixmap &pixmap)
{
    *mPx = pixmap.copy();
    setSceneRect(-mPx->width()/2, -mPx->height()/2, mPx->width(), mPx->height());
}
//------------------------------------------------------------------------------
void TSceneView::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(-mPx->width()/2, -mPx->height()/2,
            mPx->width(), mPx->height(), *mPx);
}
//------------------------------------------------------------------------------
//void TSceneView::mousePressEvent(QMouseEvent* mouseEvent)
//{
//    if( mouseEvent->button() == Qt::RightButton )
//        mFixedPoint = mouseEvent->pos();
//    QGraphicsView::mousePressEvent(mouseEvent);
//}
////------------------------------------------------------------------------------
//void TSceneView::mouseMoveEvent(QMouseEvent* mouseEvent)
//{
//    if( mFixedPoint.isNull() )
//        return;

//    QPointF offset = mapToScene(mFixedPoint) - mapToScene(mouseEvent->pos());
//    mFixedPoint = mouseEvent->pos();
//    centerOn(mFixedPoint + offset);
//    QGraphicsView::mouseMoveEvent(mouseEvent);
//}
////------------------------------------------------------------------------------
//void TSceneView::mouseReleaseEvent(QMouseEvent* mouseEvent)
//{
//    mFixedPoint = QPoint();
//    QGraphicsView::mouseReleaseEvent(mouseEvent);
//}
//------------------------------------------------------------------------------
void TSceneView::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
//    QGraphicsView::mousePressEvent(mouseEvent);
}

void TSceneView::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
//    QGraphicsView::mouseMoveEvent(mouseEvent);
}

void TSceneView::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
//    QGraphicsView::mouseReleaseEvent(mouseEvent);
}
