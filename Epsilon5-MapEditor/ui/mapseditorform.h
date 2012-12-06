// mapseditorform.h
#pragma once
#include <QWidget>
#include <QModelIndex>
//------------------------------------------------------------------------------
class TMapContainer;
class QGraphicsScene;
class QGraphicsView;
class QAbstractItemModel;
//------------------------------------------------------------------------------
namespace Ui
{
class TMapsEditorForm;
}
//------------------------------------------------------------------------------
class TMapsEditorForm : public QWidget
{
    Q_OBJECT
public:
    explicit TMapsEditorForm(QWidget* parent = 0);
    ~TMapsEditorForm();
    void setObjectsModel(QAbstractItemModel* model);

protected:
    void resizeEvent(QResizeEvent*);

private slots:
    void on_mapsView_clicked(QModelIndex index);

    void showMapListContentMenu(QPoint point);
    void updateMapSettings();
    void saveMapListAction();

private:
    Ui::TMapsEditorForm* ui;
    TMapContainer* mMaps;
    QGraphicsScene* mScene;
    QGraphicsView* mView;
};
//------------------------------------------------------------------------------
