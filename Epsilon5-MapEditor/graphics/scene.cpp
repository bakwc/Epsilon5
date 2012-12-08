#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "scene.h"
//------------------------------------------------------------------------------
TScene::TScene(QObject* parent)
    : QGraphicsScene(parent)
{
}
//------------------------------------------------------------------------------
void TScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}
//------------------------------------------------------------------------------
void TScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
//    qDebug( "%f : %f", mouseEvent->pos().x(), mouseEvent->pos().y() );
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
//------------------------------------------------------------------------------
void TScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
//------------------------------------------------------------------------------
