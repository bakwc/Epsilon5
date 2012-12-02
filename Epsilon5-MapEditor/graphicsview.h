#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSizeF>
#include <QPixmap>
#include <utils.h>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QGraphicsScene* scene, QList<utils::Object> &objsList,
                          QList<QPixmap> &objPix, QWidget *parent = 0);

    void addMapItem(const utils::MapLine &ml);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void paintEvent(QPaintEvent *event);

signals:
    
public slots:
    void selectedItem(int item);
    
private:
    QList<utils::Object> &_objsLst;
    QList<QPixmap>       &_objPix;
    int         _itemId;

    QPoint      _itemPrevPoint;
};

#endif // GRAPHICSVIEW_H
