// mapseditorform.h
#pragma once
#include <QWidget>
#include <QModelIndex>
#include "storage/st_mapcontainer.h"
//------------------------------------------------------------------------------
class TScene;
class TSceneView;
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

    void toggleBrowserBox();
    void showMapListContentMenu(QPoint point);
    void updateMapSettings();
    void updateObjectSettings();
    void updateRespawnSettings();
    void updateTeamButton();
    void saveMapListAction();
    void refreshMapListAction();

    void initScene(const QModelIndex& index);
    void keyReleaseEvent(QKeyEvent *);

private:
    Ui::TMapsEditorForm* ui;
    containers::TMapContainer* mMaps;
    TScene* mScene;
    TSceneView* mSceneView;
    int mTeamValue;
    EBrowserBoxStates mBrowserState;
};
//------------------------------------------------------------------------------
