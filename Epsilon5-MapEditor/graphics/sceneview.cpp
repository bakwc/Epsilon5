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
void TSceneView::paintEvent(QPaintEvent* event)
{
    QGraphicsView::paintEvent(event);
}
//------------------------------------------------------------------------------
void TSceneView::setBackground(const QPixmap& pixmap)
{
    setBackground(pixmap, pixmap.size());
}
//------------------------------------------------------------------------------
void TSceneView::setBackground(const QPixmap &pixmap, const QSize &sceneSize)
{
    *mPx = pixmap.copy(0, 0, sceneSize.width(), sceneSize.height());
    setSceneRect(-mPx->width() / 2, -mPx->height() / 2, mPx->width(), mPx->height());
}
//------------------------------------------------------------------------------
void TSceneView::drawBackground(QPainter* painter, const QRectF& rect)
{
    Q_UNUSED(rect);
    painter->drawPixmap(-mPx->width() / 2, -mPx->height() / 2,
            mPx->width(), mPx->height(), *mPx);
}
//------------------------------------------------------------------------------
