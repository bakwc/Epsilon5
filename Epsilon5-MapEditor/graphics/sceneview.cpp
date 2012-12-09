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
    *mPx = pixmap.copy();
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
