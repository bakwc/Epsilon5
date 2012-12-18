#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
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

    if (mButton == Qt::LeftButton) {
        mLastObject = (TStaticObject*)(itemAt(
                QPoint(mouseEvent->lastScenePos().x(),
                mouseEvent->lastScenePos().y()), QTransform()));
        if( mLastObject )
            emit clickItem(mLastObject->objectId(), mLastObject->isRespawn());
    }
}
//------------------------------------------------------------------------------
void TScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    if (mLastObject) {
        emit moveItem(mLastObject->objectId(), mLastObject->pos(),
                      mLastObject->angleRad(), mLastObject->isRespawn());
    }
}
//------------------------------------------------------------------------------
void TScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    mButton = Qt::NoButton;
    mLastObject = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
//------------------------------------------------------------------------------
