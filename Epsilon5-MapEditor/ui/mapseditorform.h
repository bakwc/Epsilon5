// mapseditorform.h
#pragma once
#include <QWidget>
#include <QModelIndex>
#include "imagecache.h"
#include "storage/st_mapcontainer.h"
//------------------------------------------------------------------------------
class TScene;
class TSceneView;
class QGraphicsView;
class QAbstractItemModel;
class QGraphicsItem;
//------------------------------------------------------------------------------
namespace Ui
{
class TMapsEditorForm;
}
//------------------------------------------------------------------------------
class TMapsEditorForm : public QWidget
{
    Q_OBJECT
    enum EBrowserBoxStates {
        E_BrowserNone = 0,
        E_BrowserHalf,
        E_BrowserFull,
        EBrowserBoxStatesCount
    };

public:
    explicit TMapsEditorForm(QWidget* parent = 0);
    ~TMapsEditorForm();
    void setObjectsModel(QAbstractItemModel* model);

protected:
    void resizeEvent(QResizeEvent*);

private slots:
    void on_mapsView_clicked(QModelIndex index);
    void on_toolBox_currentChanged(int index);
    void on_listView_clicked(QModelIndex index);
    void on_teamButton_clicked();

    void onItemMove(quint32 id, QPointF position, qreal angle);
    void toggleBrowserBox();
    void showMapListContentMenu(QPoint point);
    void showObjectsContentMenu(QPoint point);
    void showListViewContentMenu(QPoint point);
    void updateMapSettings();
    void updateObjectSettings();
    void updateRespawnSettings();
    void updateTeamButton();
    void saveMapListAction();
    void refreshMapListAction();
    void loadMapListAction();
    void newMapListAction();
    void deleteMapListAction();

    void refreshObjectsListAction();
    void loadObjectsListAction();

    void initScene(const QModelIndex& index);
    void keyReleaseEvent(QKeyEvent *);

    void timerEvent(QTimerEvent *);

private:
    Ui::TMapsEditorForm* ui;
    containers::TMapContainer* mMaps;
    containers::TMapItem* mCurrentMap;
    TScene* mScene;
    TSceneView* mSceneView;
    int mTeamValue;
    EBrowserBoxStates mBrowserState;
    TImageCache mImages;
    containers::TObjectContainer mResObjects;
};
//------------------------------------------------------------------------------
