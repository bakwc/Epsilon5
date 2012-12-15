#include <QDebug>
#include <QPaintEvent>
#include <QGraphicsSceneMouseEvent>
#include "sceneview.h"
//------------------------------------------------------------------------------
const qint8 MAX_ZOOM_TIMES = 8;
const qreal SCALE_FACTOR = 1.2;
//------------------------------------------------------------------------------
TSceneView::TSceneView(TScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
    , mFixedPoint(QPoint())
    , mPx(new QPixmap())
    , mZoomTimes(0)    // -MAX_ZOOM_TIMES <= mZoomTimes <= MAX_ZOOM_TIMES
    , mGridSize(10)
    , mGridVisible(false)
    , mGridColor(Qt::black)
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
void TSceneView::setBackground(const QPixmap& pixmap, const QSize& sceneSize)
{
    *mPx = pixmap.copy(0, 0, sceneSize.width(), sceneSize.height());
    setSceneRect(-mPx->width() / 2, -mPx->height() / 2, mPx->width(), mPx->height());
}
//------------------------------------------------------------------------------
void TSceneView::drawBackground(QPainter* painter, const QRectF& rect)
{
    Q_UNUSED(rect);
    const quint8 SCENE_BORDER_SIZE = 10;
    QRect backgroundRect(-mPx->width() / 2, -mPx->height() / 2,
        mPx->width(), mPx->height());
    painter->drawPixmap(backgroundRect, *mPx);
    QPen oldPen = painter->pen();
    painter->setPen(QPen(QBrush(Qt::black), SCENE_BORDER_SIZE));
    painter->drawRect(backgroundRect);
    painter->setPen(oldPen);

    if( mPx->isNull() )
        return;

    if( mGridVisible ) {
        // Draw grid
        drawGrid(painter, mGridSize, mGridColor);

        // Draw center point
        QPen origPen = painter->pen();
        painter->setPen(QPen(Qt::red, 10));
        painter->drawRect(0, 0, 1, 1);
        painter->setPen(origPen);
    }
}
//------------------------------------------------------------------------------
void TSceneView::drawGrid(QPainter *painter, quint16 gridSize, const QColor& color)
{
    QPointF centerPoint = QPointF(mPx->size().width() / 2, mPx->size().height() / 2);
    quint16 numRows = centerPoint.y() * 2 / gridSize;
    quint16 numCols = centerPoint.x() * 2 / gridSize;
    QPointF delta = centerPoint - QPointF(numCols / 2.0 * gridSize,
            numRows / 2.0 * gridSize);
    QVector<QPoint> points;
    QRectF drawingRect = QRectF(-centerPoint.x(), -centerPoint.y(),
            centerPoint.x(), centerPoint.y());

    // Make num* be always even
    numRows += numRows % 2;
    numCols += numCols % 2;

    for( int i = 0; i <= numCols; ++i )
    {
        points.append(QPoint(i*gridSize + drawingRect.topLeft().x() + delta.x(),
                drawingRect.top()));
        points.append(QPoint(i*gridSize + drawingRect.topLeft().x() + delta.x(),
                drawingRect.height()));
    }

    for( int i = 0; i <= numRows; ++i ) {
        points.append(QPoint(drawingRect.left(),
                i*gridSize + drawingRect.topLeft().y() + delta.y()));
        points.append(QPoint(drawingRect.width(),
                i*gridSize + drawingRect.topLeft().y() + delta.y()));
    }

    QPen origPen = painter->pen();
    painter->setPen(QPen(color));
    painter->drawLines(points);
    painter->setPen(origPen);
}
//------------------------------------------------------------------------------
void TSceneView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    mButton = event->button();
    mFixedPoint = event->pos();
}
//------------------------------------------------------------------------------
void TSceneView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    mButton = Qt::NoButton;
    mFixedPoint = event->pos();
}
//------------------------------------------------------------------------------
void TSceneView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    if(!mFixedPoint.isNull() && items(event->pos()).size() <= 0 &&
        mButton == Qt::LeftButton && event->modifiers() != Qt::ShiftModifier &&
        event->modifiers() != Qt::ControlModifier)
    {
        QPointF offset = mapToScene(mFixedPoint) - mapToScene(event->pos());
        mFixedPoint = event->pos();
        setCenter(center() + offset);
    }
}
//------------------------------------------------------------------------------
void TSceneView::wheelEvent(QWheelEvent *event)
{
    if( event->modifiers() == Qt::ControlModifier) {
        resetZoom();
        return;
    }

    QPointF pointBeforeScale(mapToScene(event->pos()));
    QPointF visibleCenter = center();

    if(event->delta() > 0) {
        if( mZoomTimes <= MAX_ZOOM_TIMES ) {
            scale(SCALE_FACTOR, SCALE_FACTOR);
            ++mZoomTimes;
        }
    } else if (mZoomTimes >= -MAX_ZOOM_TIMES) {
        scale(1.0 / SCALE_FACTOR, 1.0 / SCALE_FACTOR);
        --mZoomTimes;
    }

    QPointF pointAfterScale(mapToScene(event->pos()));
    QPointF offset = pointBeforeScale - pointAfterScale;
    QPointF newCenter = visibleCenter + offset;
    setCenter(newCenter);
}
//------------------------------------------------------------------------------
void TSceneView::setCenter(const QPointF &centerPoint)
{
    QRectF visibleArea = mapToScene(viewport()->rect()).boundingRect();
    QRectF sceneBounds = sceneRect();

    qreal boundX = 0;
    qreal boundY = 0;
    qreal boundWidth = sceneBounds.width() - visibleArea.width();
    qreal boundHeight = sceneBounds.height() - visibleArea.height();
    QRectF bounds(boundX, boundY, boundWidth, boundHeight);

    mCenterPoint = centerPoint;

    if(!bounds.contains(centerPoint)) {
        if(visibleArea.contains(sceneBounds)) {
            mCenterPoint = sceneBounds.center();
        } else {
            if(centerPoint.x() > bounds.x() + bounds.width() / 2)
                mCenterPoint.setX(bounds.x() + bounds.width() / 2);
            else if(centerPoint.x() < bounds.x() - bounds.width() / 2)
                mCenterPoint.setX(bounds.x() - bounds.width() / 2 );

            if(centerPoint.y() > bounds.y() + bounds.height() / 2)
                mCenterPoint.setY(bounds.y() + bounds.height() / 2);
            else if(centerPoint.y() < bounds.y() - bounds.height() / 2)
                mCenterPoint.setY(bounds.y() - bounds.height() / 2);
        }
    }
    centerOn(mCenterPoint);
}
//------------------------------------------------------------------------------
QPointF TSceneView::center()
{
    return mCenterPoint;
}
//------------------------------------------------------------------------------
void TSceneView::resizeEvent(QResizeEvent* event) {
    QRectF visibleArea = mapToScene(rect()).boundingRect();
    setCenter(visibleArea.center());
    QGraphicsView::resizeEvent(event);
}
//------------------------------------------------------------------------------
void TSceneView::clear()
{
    setBackground(QPixmap());
}
//------------------------------------------------------------------------------
void TSceneView::resetZoom()
{
    if( !mZoomTimes )
        return;

    QPointF visibleCenter = center();
    double scaleFactor = mZoomTimes < 0 ? SCALE_FACTOR : 1 / SCALE_FACTOR;
    for( int i = 0; i < abs(mZoomTimes); ++i) {
        scale(scaleFactor, scaleFactor);
    }

    mZoomTimes = 0;
    setCenter(visibleCenter);
}
//------------------------------------------------------------------------------
void TSceneView::setGridSize(quint16 size) {
    mGridSize = size;
}
//------------------------------------------------------------------------------
void TSceneView::setGridColor(const QColor& color) {
    mGridColor = color;
}
//------------------------------------------------------------------------------
void TSceneView::setGridVisible(bool value) {
    mGridVisible = value;
}
//------------------------------------------------------------------------------
quint16 TSceneView::gridSize() const {
    return mGridSize;
}
//------------------------------------------------------------------------------
QColor TSceneView::gridColor() const {
    return mGridColor;
}
//------------------------------------------------------------------------------
bool TSceneView::isGridVisible() const {
    return mGridVisible;
}
//------------------------------------------------------------------------------
