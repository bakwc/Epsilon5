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

public slots:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

};
//------------------------------------------------------------------------------
