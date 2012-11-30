#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QGraphicsScene* scene, QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // GRAPHICSVIEW_H
