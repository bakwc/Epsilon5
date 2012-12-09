#pragma once
#include <QGraphicsScene>
//------------------------------------------------------------------------------
class TScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit TScene(QObject* parent = 0);
    void init();

signals:
    void moveItem(quint32 id, QPointF position, qreal angle);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

private:
    Qt::MouseButton mButton;
    QPointF mOriginPos;
    QPointF mLastObjectPos;
};
//------------------------------------------------------------------------------
