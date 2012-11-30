#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSizeF>
#include <QPixmap>


class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QGraphicsScene* scene, QWidget *parent = 0);
    
    void setItem(const QString &str, const QSizeF &s, const QPixmap &pix);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void paintEvent(QPaintEvent *event);

signals:
    
public slots:
    
private:
    QPixmap     _itemPix;
    QString     _itemName;
    QSizeF      _itemSize;
    QPoint      _itemPrevPoint;
};

#endif // GRAPHICSVIEW_H
