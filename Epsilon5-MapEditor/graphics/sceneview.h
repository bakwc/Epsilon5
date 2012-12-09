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
    void drawBackground(QPainter* painter, const QRectF& rect);
    void paintEvent(QPaintEvent* event);

private:
    QPoint mFixedPoint;
    QPixmap* mPx;
};
//------------------------------------------------------------------------------
