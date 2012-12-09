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


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void drawBackground(QPainter *painter, const QRectF &rect);

//    void mousePressEvent(QMouseEvent* mouseEvent);
//    void mouseMoveEvent(QMouseEvent* mouseEvent);
//    void mouseReleaseEvent(QMouseEvent* mouseEvent);

public slots:
//    void moveCenterOn(const QPointF* pos);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPoint mFixedPoint;
    QPixmap* mPx;
};
//------------------------------------------------------------------------------
