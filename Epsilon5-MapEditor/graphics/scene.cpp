#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "staticobject.h"
#include "scene.h"
//------------------------------------------------------------------------------
TScene::TScene(QObject* parent)
    : QGraphicsScene(parent)
    , mButton(Qt::NoButton)
    , mOriginPos(QPointF())
    , mLastObjectPos(QPointF())
{
}
//------------------------------------------------------------------------------
void TScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
    mButton = mouseEvent->button();
    mOriginPos = mouseEvent->lastScenePos();
//    if (button != Qt::LeftButton) {
//        return;
//    }
}
//------------------------------------------------------------------------------
void TScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
//    if( mouseEvent->button() == Qt::LeftButton ){
//        qDebug( "asada" );
//    }

    if( mButton == Qt::LeftButton ){
        TStaticObject* item = (TStaticObject*)(itemAt(
            QPoint(mouseEvent->lastScenePos().x(), mouseEvent->lastScenePos().y())));
        if( item ){
            emit moveItem(item->objectId(), item->pos(), item->rotation());//item);//&mLastObjectPos);
        }
//        qDebug("%f %f", mouseEvent->pos().x(), mouseEvent->pos().y());
//        emit viewportMoved(mouseEvent->pos());
//        qDebug("%f %f", mouseEvent->pos().x() + 1 - mOriginPos.x(),
//            mouseEvent->pos().y() - mOriginPos.y());
//        emit viewportMoved(QPointF(mouseEvent->pos().x() - mOriginPos.x(),
//            mouseEvent->pos().y() - mOriginPos.y()));
//        qDebug( "%fx%f %fx%f",
//                mouseEvent->pos().x(), mouseEvent->pos().y(),
//                mOriginPos.x(), mOriginPos.y());

//        qDebug( "%fx%f %fx%f",
//                mouseEvent->pos().x(), mouseEvent->pos().y(),
//                mouseEvent->lastScenePos().x(), mouseEvent->lastScenePos().y());
//            qDebug( "%fx%f",
//                mouseEvent->lastScenePos().x(),// - sceneRect().width()/2,
//                mouseEvent->lastScenePos().y());// - sceneRect().height()/2);
//            qDebug( "%f xx %f", mouseEvent->lastScenePos().x() - mOriginPos.x(),
//                mouseEvent->lastScenePos().y() - mOriginPos.y());
//            mOriginPos = mouseEvent->lastScenePos();
        //QPointF pp = this->

//        qDebug( "%fx%f %fx%f",
//                mouseEvent->pos().x(), mouseEvent->pos().y(),
//                mOriginPos.x(), mOriginPos.y());
//        mOriginPos = mouseEvent->pos() + (mouseEvent->pos() - mOriginPos);

//        emit viewportMoved(&mOriginPos);
            //QPointF(
//            mouseEvent->lastScenePos().x(),// - sceneRect().width()/2,
//            mouseEvent->lastScenePos().y()));// - sceneRect().height()/2));
//            /*mOriginPos.x() + */*/mouseEvent->lastScenePos().x() - mOriginPos.x(),
//            /*mOriginPos.y() + */mouseEvent->lastScenePos().y() - mOriginPos.y());*/
        return;
    }
}
//------------------------------------------------------------------------------
void TScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    mButton = Qt::NoButton;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
//------------------------------------------------------------------------------
