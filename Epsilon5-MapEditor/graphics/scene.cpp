#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "staticobject.h"
#include "scene.h"
//------------------------------------------------------------------------------
TScene::TScene(QObject* parent)
    : QGraphicsScene(parent)
    , mButton(Qt::NoButton)
    , mOriginPos(QPointF(0, 0))
{
}
//------------------------------------------------------------------------------
void TScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
    mButton = mouseEvent->button();
    mOriginPos = mouseEvent->pos();
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
//        qDebug("%f %f", mouseEvent->pos().x(), mouseEvent->pos().y());
//        emit viewportMoved(mouseEvent->pos());
//        qDebug("%f %f", mouseEvent->pos().x() + 1 - mOriginPos.x(),
//            mouseEvent->pos().y() - mOriginPos.y());
//        emit viewportMoved(QPointF(mouseEvent->pos().x() - mOriginPos.x(),
//            mouseEvent->pos().y() - mOriginPos.y()));
        qDebug( "%fx%f %fx%f", mouseEvent->pos().x(), mouseEvent->pos().y(),
                mOriginPos.x(), mOriginPos.y());
        mOriginPos = mouseEvent->pos() + (mouseEvent->pos() - mOriginPos);
        emit viewportMoved(mOriginPos);
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
void TScene::setBackground(const QPixmap &pixmap)
{
    TStaticObject* backgroundObject = new TStaticObject(pixmap);
    backgroundObject->setFixed();
    backgroundObject->setPos( -backgroundObject->pixmap().width()/2,
            -backgroundObject->pixmap().height()/2);
    addItem(backgroundObject);
}
//------------------------------------------------------------------------------
