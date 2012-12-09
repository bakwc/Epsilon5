#include <QGraphicsSceneMouseEvent>
#include "sceneview.h"
//------------------------------------------------------------------------------
TSceneView::TSceneView(TScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
    , mCursor(QPointF(0, 0))
{
}
//------------------------------------------------------------------------------
void TSceneView::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug("dfsdf");
    if( mouseEvent->button() == Qt::LeftButton )
    {
        qDebug("Ssss");
//        scrollContentsBy(mouseEvent->pos().x() - mCursor.x(),
//                mouseEvent->pos().y() - mCursor.y());
        return;
    }
    QGraphicsView::mouseMoveEvent((QMouseEvent*)mouseEvent);
}
//------------------------------------------------------------------------------
void TSceneView::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if( mouseEvent->button() == Qt::LeftButton )
    {
        mCursor = mouseEvent->pos();
        return;
    }
    QGraphicsView::mousePressEvent((QMouseEvent*)mouseEvent);
}
//------------------------------------------------------------------------------
void TSceneView::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
//    releaseMouse();
    QGraphicsView::mouseReleaseEvent((QMouseEvent*)mouseEvent);
}
//------------------------------------------------------------------------------
void TSceneView::moveCenterOn(const QPointF& pos)
{
//    qDebug("%s", qPrintable(QString(Q_FUNC_INFO).append(":: %1 %2")
//            .arg(pos.x()).arg(pos.y())));
////    QPointF xx = mapFromScene(pos);

//    qDebug("%s", qPrintable(QString(Q_FUNC_INFO).append(":: %1 %2")
//            .arg(xx.x()).arg(xx.y())));
//    if( pos.x() || pos.y() ) {
//        centerOn(mapFromScene(pos));
//    }
}
