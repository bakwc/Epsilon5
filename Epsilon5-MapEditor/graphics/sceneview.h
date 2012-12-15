#pragma once
#include <QGraphicsView>
#include "graphics/scene.h"
//------------------------------------------------------------------------------
class TSceneView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TSceneView(TScene* scene, QWidget* parent = 0);
    void setBackground(const QPixmap& pixmap);
    void setBackground(const QPixmap& pixmap, const QSize& sceneSize);

public slots:
    void clear();
    void resetZoom();

protected:
    void drawBackground(QPainter* painter, const QRectF& rect);
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent* event);

    void setCenter(const QPointF& centerPoint);
    QPointF center();

private:
    QPoint mFixedPoint;
    QPointF mCenterPoint;
    QPixmap* mPx;
    Qt::MouseButton mButton;
    qint8 mZoomTimes;
};
//------------------------------------------------------------------------------
