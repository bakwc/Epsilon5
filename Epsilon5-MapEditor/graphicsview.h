// graphicsview.h
#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSizeF>
#include <QPixmap>
#include <utils.h>
#include "mapitemsignal.h"
//------------------------------------------------------------------------------
class TGraphicsView : public QGraphicsView {
    Q_OBJECT
public:
    typedef QList<QPixmap> TPixmapsList;
    typedef QList<utils::TObject> TObjectsList;

public:
    explicit TGraphicsView(QGraphicsScene* scene, TObjectsList& objectsList,
            TPixmapsList& pixmapsList, QWidget* parent = 0);
    void addMapItem(const utils::TMapLine& ml);

protected:
    void mouseDoubleClickEvent(QMouseEvent* event);
//    void mouseMoveEvent(QMouseEvent* event);
//    void paintEvent(QPaintEvent* event);

public slots:
    void selectedItem(int item);
    void itemSlot(QString name, QPointF itemPos, qreal itemRot);

private:
    TObjectsList& mObjectsList;
    TPixmapsList& mPixmapsList;
    int mItemId;
    QPoint mItemPrevPoint;
    MapItemSignal mItemSignal;
};
//------------------------------------------------------------------------------
